#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Listing
{
	int id;
	int host_id;
	int min_nights;
	int noof_reviews;
	int calhostlistcnt;
	int avail_365;
	char *hostname;
	char *neighhood_grp;
	char *neighhood;
	char *room_type;
	float price;
	float latitude;
	float longitude;	
};

char title_header[4096];

void displayfiledata(struct Listing *tempptr, int records_cnt)
{
	for(int cnt = 0; cnt < records_cnt; cnt++)
	{
		printf("id : %d, host_id : %d, host_name : %s, neighbourhood_group : %s, neighbourhood : %s, latitude : %f, longitude : %f,room type : %s, price : %f, minimum nights : %d, No.of reviews : %d, Cal.host listing count : %d, availability 365 : %d\n",(tempptr+cnt)->id,(tempptr+cnt)->host_id,(tempptr+cnt)->hostname, (tempptr+cnt)->neighhood_grp, (tempptr+cnt)->neighhood,(tempptr+cnt)->latitude,(tempptr+cnt)->longitude, (tempptr+cnt)->room_type, (tempptr+cnt)->price, (tempptr+cnt)->min_nights, (tempptr+cnt)->noof_reviews, (tempptr+cnt)->calhostlistcnt, (tempptr+cnt)->avail_365);
	}
}

static int findnoofrecords()
{
	int line_cnt = 0;
	char *buff = NULL;
	size_t line_size = 0;
	FILE *fp = NULL;

	fp = fopen("listings.csv", "r");
	if(fp == NULL)
	{
		printf("Unable to open csv file\n");
		return -1;
	}

	while(getline(&buff, &line_size, fp) != -1)
	{
			
		//printf("line data : %s, line size : %ld\n", buff, line_size);
		line_cnt ++;			
	}
	fclose(fp);	
	return line_cnt;
}

static int sortbyprice(const void *price_1, const void *price_2)
{
        return (((struct Listing*)price_1)->price - ((struct Listing*)price_2)->price);
}


static int pricesortfun(struct Listing *ptrprice, int records_cnt)
{
	
	qsort(ptrprice, records_cnt, sizeof(struct Listing), sortbyprice);
	return 0;
}

static int sortbyhostname(const void *hostname1, const void *hostname2)
{
        return strcmp(((struct Listing*)hostname1)->hostname, ((struct Listing*)hostname2)->hostname);
}

static int hostnamesortfun(struct Listing *ptrhostname, int records_cnt)
{

	qsort(ptrhostname, records_cnt, sizeof(struct Listing), sortbyhostname);
	return 0;
}

static int storesorteddata(struct Listing *tmp, int rcdcnt, int sort_type)
{
	FILE *fp_price = NULL;
	FILE *fp_hostname = NULL;
	
	if(sort_type == 1)
	{
		fp_price = fopen("price_listing.csv", "w");
		if(fp_price == NULL)
		{
			printf("Unable to create the file\n");
			return -1;
		}
		else
		{
			printf("File data sorted by price \n");
			fprintf(fp_price,"%s",title_header);
			for(int cnt = 0; cnt < rcdcnt; cnt++)
			{
				fprintf(fp_price, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",(tmp+cnt)->id,(tmp+cnt)->host_id,(tmp+cnt)->hostname,(tmp+cnt)->neighhood_grp,(tmp+cnt)->neighhood,(tmp+cnt)->latitude,(tmp+cnt)->longitude,(tmp+cnt)->room_type,(tmp+cnt)->price,(tmp+cnt)->min_nights,(tmp+cnt)->noof_reviews,(tmp+cnt)->calhostlistcnt,(tmp+cnt)->avail_365);
			}	
		}
		fclose(fp_price);
		
	}
	else
	{
		fp_hostname = fopen("hostname_listing.csv", "w");
		if(fp_hostname == NULL)
		{
			printf("Unable to create the file \n");
			return -1;
		}
		else
		{
			printf("File data sorted by hostname \n");

			fprintf(fp_hostname,"%s",title_header);
			for(int cnt = 0; cnt < rcdcnt; cnt++)
			{
				fprintf(fp_hostname, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n",(tmp+cnt)->id,(tmp+cnt)->host_id,(tmp+cnt)->hostname,(tmp+cnt)->neighhood_grp,(tmp+cnt)->neighhood,(tmp+cnt)->latitude,(tmp+cnt)->longitude,(tmp+cnt)->room_type,(tmp+cnt)->price,(tmp+cnt)->min_nights,(tmp+cnt)->noof_reviews,(tmp+cnt)->calhostlistcnt,(tmp+cnt)->avail_365);
			}	
		}
		fclose(fp_hostname);
		
	}
}

int main(void)
{
	char data[64];
	int user_sort = 0;
	
	FILE *fp = NULL;
	char *single_line = NULL;
	size_t line_length = 0;
	int noofrecords = 0;
	char *temp = NULL;
	int cnt = 0;
	
	struct Listing *LstPtr = NULL;
	
	noofrecords = findnoofrecords();
	//printf("No.of records : %d\n",noofrecords);

	fp = fopen("listings.csv", "r");
	if(fp == NULL)
	{
		printf("Unable to open csv file \n");
		return -1;
	}
	else
	{
		fgets(title_header, 2048, fp);
		LstPtr = (struct Listing*)malloc(noofrecords * (sizeof(struct Listing)));
		if(LstPtr == NULL)
		{
			printf("memory allocation failed!!!");
			return -1;
		}
		//Skip the headers
		getline(&single_line, &line_length, fp);

		while(getline(&single_line, &line_length, fp) != -1)
		{
			temp = strtok(single_line,",");
			(LstPtr+cnt)->id = atoi(temp);
			
			temp = strtok(NULL,",");
			(LstPtr+cnt)->host_id = atoi(temp);
			
			(LstPtr+cnt)->hostname =strdup(strtok(NULL,","));
			(LstPtr+cnt)->neighhood_grp =strdup(strtok(NULL,","));
			(LstPtr+cnt)->neighhood =strdup(strtok(NULL,","));

			temp = strtok(NULL,",");
			(LstPtr+cnt)->latitude = atof(temp);
			
			temp = strtok(NULL,",");
			(LstPtr+cnt)->longitude = atof(temp);
			
			(LstPtr+cnt)->room_type =strdup(strtok(NULL,","));
			
			temp = strtok(NULL,",");			
			(LstPtr+cnt)->price = atof(temp);
			
			temp = strtok(NULL,",");
			(LstPtr+cnt)->min_nights = atoi(temp);
			
			temp = strtok(NULL,",");
			(LstPtr+cnt)->noof_reviews = atoi(temp);
			
			temp = strtok(NULL,",");
			(LstPtr+cnt)->calhostlistcnt = atoi(temp);
			
			temp = strtok(NULL,",");
			(LstPtr+cnt)->avail_365 = atoi(temp);
			
			cnt++;
			
		}
		
//		displayfiledata(LstPtr, cnt);

		pricesortfun(LstPtr, cnt);
		storesorteddata(LstPtr, cnt, 1);
	
		hostnamesortfun(LstPtr, cnt);
		storesorteddata(LstPtr, cnt, 2);
		
	}

	fclose(fp);
	free(LstPtr);
	
   return 0;
}
