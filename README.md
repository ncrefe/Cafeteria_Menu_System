# Cafeteria_Menu_System
This C code implements a cafeteria menu system that calculates the monthly income based on menu details and total sales. The code utilizes a global structure named "cafeteria" which consists of three different arrays and the name of the month for the given menu. The structure is defined as follows:
```
typedef struct {
    char* date;
    char* soup;
    char* main_dish;
    char* side_dish;
    char* extra;
    int sale_count[3];
} Menu;
```
The "cafeteria" structure contains pointers for the normal menu array, vegan menu array, and vegetarian menu array. Each array holds menu structs corresponding to the number of days food has been served in a month.

The code provides the following functions:

```
void initialize_menus(Cafeteria *cafeteria, char *csv_file_name)
```
This function initializes the global "cafeteria" struct and menu structs by reading the menu details from a CSV file. The name of the month is extracted from the CSV file name. All count arrays for each day are initialized as 0. Dynamic memory allocation is used appropriately.

```
void record_customer_counts(Cafeteria *cafeteria)
```
This function generates random customer counts for each type (student, academic personal, administrative personal) for each menu of each day in the cafeteria. The count arrays for each type are updated according to the random counts. Random numbers range from 0 to 50.

```
void calc_and_show_income(Cafeteria *cafeteria)
```

This function calculates and displays the total income in three different ways:

a. The distribution of the total gained money on the type of menus.

b. Overall sales for a month using the customer counts within each menu.

c. Total sales income of the whole month.

The prices for each customer type are fixed (student: 6 TL, academic personal: 16 TL, administrative personal: 12 TL), and the type of menu does not affect the price.

You can call these functions with the initialized cafeteria struct as input to obtain the sales results at the end of the month.
