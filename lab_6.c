#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold a single entry
struct Listing {
    char host_name[100];
    char price[20];
    // Add more fields as needed
};

// Function to read data from the CSV file
int read_listings_csv(const char* file_path, struct Listing** data, int* num_entries) {
    FILE* file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the header line (assuming the first line contains column names)
    char header[512];
    if (fgets(header, sizeof(header), file) == NULL) {
        perror("Error reading header");
        fclose(file);
        return 1;
    }

    // Count the number of entries in the CSV
    int num_lines = 0;
    while (fgets(header, sizeof(header), file) != NULL) {
        num_lines++;
    }

    // Allocate memory for the data
    *data = (struct Listing*)malloc(num_lines * sizeof(struct Listing));
    if (*data == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return 1;
    }

    // Reset the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Skip the header line
    fgets(header, sizeof(header), file);

    // Read data into the array of structs
    int i = 0;
    while (fgets(header, sizeof(header), file) != NULL) {
        sscanf(header, "%[^,],%s", (*data)[i].host_name, (*data)[i].price);
        // Add more fields as needed and update sscanf accordingly
        i++;
    }

    *num_entries = num_lines;

    fclose(file);
    return 0;
}

// Function to compare two listings by host_name for sorting
int compare_by_host_name(const void* a, const void* b) {
    struct Listing* listingA = (struct Listing*)a;
    struct Listing* listingB = (struct Listing*)b;
    return strcmp(listingA->host_name, listingB->host_name);
}

// Function to compare two listings by price for sorting
int compare_by_price(const void* a, const void* b) {
    struct Listing* listingA = (struct Listing*)a;
    struct Listing* listingB = (struct Listing*)b;
    // Assuming prices are stored as strings with a currency symbol, e.g., "$100.00"
    float priceA = atof(strchr(listingA->price, '$') + 1);
    float priceB = atof(strchr(listingB->price, '$') + 1);
    if (priceA < priceB) return -1;
    else if (priceA > priceB) return 1;
    return 0;
}

int main() {
    const char* input_file = "listings.csv";
    struct Listing* data;
    int num_entries;

    if (read_listings_csv(input_file, &data, &num_entries) == 0) {
        // Sort by host_name
        qsort(data, num_entries, sizeof(struct Listing), compare_by_host_name);
        printf("Sorted by host_name:\n");
        for (int i = 0; i < num_entries; i++) {
            printf("Host Name: %s, Price: %s\n", data[i].host_name, data[i].price);
        }

        // Sort by price
        qsort(data, num_entries, sizeof(struct Listing), compare_by_price);
        printf("\nSorted by price:\n");
        for (int i = 0; i < num_entries; i++) {
            printf("Host Name: %s, Price: %s\n", data[i].host_name, data[i].price);
        }

        free(data); // Don't forget to free the allocated memory
    }

    return 0;
}
