#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int global_day_count = 0;

void remove_quotes(char *str) {
    int len = strlen(str);
    if (len >= 2 && str[0] == '\"' && str[len - 1] == '\"') {
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

void count_normal_menus(char *csv_file_name) {
    FILE *csv_file = fopen(csv_file_name, "r");
    if (csv_file == NULL) {
        printf("Error opening file while counting %s", csv_file_name);
        exit(1);
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), csv_file)) {
        char *menu_type = strtok(line, ",");
        remove_quotes(menu_type);
        if (strcmp(menu_type, "Normal") == 0) {
            count++;
        }
    }
    fclose(csv_file);
    global_day_count = count;
}

typedef struct Normal_Menu {
    char date[16];
    char soup[64];
    char main_dish[64];
    char side_dish[64];
    char extra[64];
    int sale_count[3];
} Normal_Menu;

typedef struct Vegan_Menu {
    char date[16];
    char soup[64];
    char main_dish[64];
    char side_dish[64];
    char extra[64];
    int sale_count[3];
} Vegan_Menu;

typedef struct Vegetarian_Menu {
    char date[16];
    char soup[64];
    char main_dish[64];
    char side_dish[64];
    char extra[64];
    int sale_count[3];
} Vegetarian_Menu;

typedef struct Cafeteria {
    char month_name[50];
    struct Normal_Menu *normal_menu_array;
    struct Vegan_Menu *vegan_menu_array;
    struct Vegetarian_Menu *vegetarian_menu_array;
} Cafeteria;

char *extract_month(char *filename) {
    char *delimiter = "_";
    char *start = strstr(filename, delimiter);
    start++; // move the pointer past the delimiter
    char *end = strstr(start, delimiter);
    int length = end - start;
    // allocate memory for the month string
    char *month = malloc(length + 1);
    strncpy(month, start, length);
    // add a null terminator to the end of the string
    month[length] = '\0';
    return month;
}

void initialize_menus(Cafeteria *cafeteria, char *csv_file_name) {
    FILE *csv_file = fopen(csv_file_name, "r");
    if (csv_file == NULL) {
        printf("Error opening file %s", csv_file_name);
        exit(1);
    }

    strcpy(cafeteria->month_name, extract_month(csv_file_name));

    // allocate memory for the menu arrays
    cafeteria->normal_menu_array = malloc(global_day_count * sizeof(Normal_Menu));
    cafeteria->vegan_menu_array = malloc(global_day_count * sizeof(Vegan_Menu));
    cafeteria->vegetarian_menu_array = malloc(global_day_count * sizeof(Vegetarian_Menu));

    // read the lines and create the menus
    char line[256];
    int normal_menu_index = 0;
    int vegan_menu_index = 0;
    int vegetarian_menu_index = 0;
    while (fgets(line, sizeof(line), csv_file)) {
        // parse the line
        char *menu_type = strtok(line, ",");
        char *date = strtok(NULL, ",");
        char *soup = strtok(NULL, ",");
        char *main_dish = strtok(NULL, ",");
        char *side_dish = strtok(NULL, ",");
        char *extra = strtok(NULL, ",");

        // remove the new line character
        extra[strlen(extra) - 1] = '\0';
        remove_quotes(menu_type);

        if (strcmp(menu_type, "Normal") == 0) {
            Normal_Menu *menu = (Normal_Menu *) malloc(sizeof(Normal_Menu));
            strcpy(menu->date, date);
            strcpy(menu->soup, soup);
            strcpy(menu->main_dish, main_dish);
            strcpy(menu->side_dish, side_dish);
            strcpy(menu->extra, extra);
            menu->sale_count[0] = 0;
            menu->sale_count[1] = 0;
            menu->sale_count[2] = 0;
            // add the menu to the array
            cafeteria->normal_menu_array[normal_menu_index] = *menu;
            normal_menu_index++;

        } else if (strcmp(menu_type, "Vegan") == 0) {
            Vegan_Menu *menu = (Vegan_Menu *) malloc(sizeof(Vegan_Menu));
            strcpy(menu->date, date);
            strcpy(menu->soup, soup);
            strcpy(menu->main_dish, main_dish);
            strcpy(menu->side_dish, side_dish);
            strcpy(menu->extra, extra);
            menu->sale_count[0] = 0;
            menu->sale_count[1] = 0;
            menu->sale_count[2] = 0;
            cafeteria->vegan_menu_array[vegan_menu_index] = *menu;
            vegan_menu_index++;

        } else if (strcmp(menu_type, "Vegetarian") == 0) {
            Vegetarian_Menu *menu = (Vegetarian_Menu *) malloc(sizeof(Vegetarian_Menu));
            strcpy(menu->date, date);
            strcpy(menu->soup, soup);
            strcpy(menu->main_dish, main_dish);
            strcpy(menu->side_dish, side_dish);
            strcpy(menu->extra, extra);
            menu->sale_count[0] = 0;
            menu->sale_count[1] = 0;
            menu->sale_count[2] = 0;
            cafeteria->vegetarian_menu_array[vegetarian_menu_index] = *menu;
            vegetarian_menu_index++;
        }
    }
    fclose(csv_file);
}

void make_upper_case(char *str) {
    int i = 0;
    while (str[i]) {
        str[i] = toupper(str[i]);
        i++;
    }
}

void print_all_menus(Cafeteria *cafeteria) {
    int days_in_month = global_day_count;
    make_upper_case(cafeteria->month_name);
    printf("***********************************************CAFETERIA MENU FOR %s MONTH****************************************\n\n", cafeteria->month_name);
    for (int i = 0; i < days_in_month; ++i) {
        printf("DATE:%s\nNormal Menu: %s, %s, %s, %s\nSales Count: Student:%d, Academic Personal:%d, Administrative Personal:%d \n",
               cafeteria->normal_menu_array[i].date,
               cafeteria->normal_menu_array[i].soup,
               cafeteria->normal_menu_array[i].main_dish,
               cafeteria->normal_menu_array[i].side_dish,
               cafeteria->normal_menu_array[i].extra,
               cafeteria->normal_menu_array[i].sale_count[0],
               cafeteria->normal_menu_array[i].sale_count[1],
               cafeteria->normal_menu_array[i].sale_count[2]);

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        printf("DATE:%s\nVegan Menu: %s, %s, %s, %s\nSales Count: Student:%d, Academic Personal:%d, Administrative Personal:%d \n",
               cafeteria->vegan_menu_array[i].date,
               cafeteria->vegan_menu_array[i].soup,
               cafeteria->vegan_menu_array[i].main_dish,
               cafeteria->vegan_menu_array[i].side_dish,
               cafeteria->vegan_menu_array[i].extra,
               cafeteria->vegan_menu_array[i].sale_count[0],
               cafeteria->vegan_menu_array[i].sale_count[1],
               cafeteria->vegan_menu_array[i].sale_count[2]);

        printf("---------------------------------------------------------------------------------------------------------------------\n");

        printf("DATE:%s\nVegetarian Menu: %s, %s, %s, %s\nSales Count: Student:%d, Academic Personal:%d, Administrative Personal:%d \n",
               cafeteria->vegetarian_menu_array[i].date,
               cafeteria->vegetarian_menu_array[i].soup,
               cafeteria->vegetarian_menu_array[i].main_dish,
               cafeteria->vegetarian_menu_array[i].side_dish,
               cafeteria->vegetarian_menu_array[i].extra,
               cafeteria->vegetarian_menu_array[i].sale_count[0],
               cafeteria->vegetarian_menu_array[i].sale_count[1],
               cafeteria->vegetarian_menu_array[i].sale_count[2]);

        printf("---------------------------------------------------------------------------------------------------------------------\n");

    }
}

void record_customer_counts(Cafeteria *cafeteria) {
    int days_in_month = global_day_count;

    for (int i = 0; i < days_in_month; ++i) {
        cafeteria->normal_menu_array[i].sale_count[0] = rand() % 50;
        cafeteria->normal_menu_array[i].sale_count[1] = rand() % 50;
        cafeteria->normal_menu_array[i].sale_count[2] = rand() % 50;
    }

    for (int i = 0; i < days_in_month; ++i) {
        cafeteria->vegan_menu_array[i].sale_count[0] = rand() % 50;
        cafeteria->vegan_menu_array[i].sale_count[1] = rand() % 50;
        cafeteria->vegan_menu_array[i].sale_count[2] = rand() % 50;
    }

    for (int i = 0; i < days_in_month; ++i) {
        cafeteria->vegetarian_menu_array[i].sale_count[0] = rand() % 50;
        cafeteria->vegetarian_menu_array[i].sale_count[1] = rand() % 50;
        cafeteria->vegetarian_menu_array[i].sale_count[2] = rand() % 50;
    }
}

void calc_and_show_income(Cafeteria *cafeteria) {
    int student_price = 6;
    int academic_personal_price = 16;
    int administrative_personal_price = 12;

    int normal_menu_student_income = 0;
    int normal_menu_academic_personal_income = 0;
    int normal_menu_administrative_personal_income = 0;

    int vegan_menu_student_income = 0;
    int vegan_menu_academic_personal_income = 0;
    int vegan_menu_administrative_personal_income = 0;

    int vegetarian_menu_student_income = 0;
    int vegetarian_menu_academic_personal_income = 0;
    int vegetarian_menu_administrative_personal_income = 0;

    for (int i = 0; i < global_day_count; ++i) {
        normal_menu_student_income += cafeteria->normal_menu_array[i].sale_count[0] * student_price;
        normal_menu_academic_personal_income += cafeteria->normal_menu_array[i].sale_count[1] * academic_personal_price;
        normal_menu_administrative_personal_income +=
                cafeteria->normal_menu_array[i].sale_count[2] * administrative_personal_price;

        vegan_menu_student_income += cafeteria->vegan_menu_array[i].sale_count[0] * student_price;
        vegan_menu_academic_personal_income += cafeteria->vegan_menu_array[i].sale_count[1] * academic_personal_price;
        vegan_menu_administrative_personal_income +=
                cafeteria->vegan_menu_array[i].sale_count[2] * administrative_personal_price;

        vegetarian_menu_student_income += cafeteria->vegetarian_menu_array[i].sale_count[0] * student_price;
        vegetarian_menu_academic_personal_income +=
                cafeteria->vegetarian_menu_array[i].sale_count[1] * academic_personal_price;
        vegetarian_menu_administrative_personal_income +=
                cafeteria->vegetarian_menu_array[i].sale_count[2] * administrative_personal_price;
    }

    printf("**************************************************THE SALES RESULTS**************************************************\n\n");

    // a.The distribution of the total gained money on the type of menus. For example, “normal menu: 1526 TL, vegan menu: 218 TL, vegetarian menu: 120 TL”.
    printf("Normal menu: %d TL, Vegan menu: %d TL, Vegetarian menu: %d TL\n",
           normal_menu_student_income + normal_menu_academic_personal_income +
           normal_menu_administrative_personal_income,
           vegan_menu_student_income + vegan_menu_academic_personal_income + vegan_menu_administrative_personal_income,
           vegetarian_menu_student_income + vegetarian_menu_academic_personal_income +
           vegetarian_menu_administrative_personal_income);

    // b.Overall sales for a month using the customer counts within each menu. For example, “students: 922 TL, Academic personal: 538 TL, Administrative personal: 404 TL”.
    printf("Students: %d TL, Academic personal: %d TL, Administrative personal: %d TL\n",
           normal_menu_student_income + vegan_menu_student_income + vegetarian_menu_student_income,
           normal_menu_academic_personal_income + vegan_menu_academic_personal_income +
           vegetarian_menu_academic_personal_income,
           normal_menu_administrative_personal_income + vegan_menu_administrative_personal_income +
           vegetarian_menu_administrative_personal_income);

    // c.Total sales income of the whole month i.e., summation of the values above. For example, “Total sale income: 1864 TL”.
    printf("Total sale income: %d TL\n\n",
           normal_menu_student_income + normal_menu_academic_personal_income +
           normal_menu_administrative_personal_income +
           vegan_menu_student_income + vegan_menu_academic_personal_income + vegan_menu_administrative_personal_income +
           vegetarian_menu_student_income + vegetarian_menu_academic_personal_income +
           vegetarian_menu_administrative_personal_income);
}

int main() {
    count_normal_menus("cafeteria_march_menu.csv");

    Cafeteria *cafeteria = malloc(sizeof(Cafeteria));

    initialize_menus(cafeteria, "cafeteria_march_menu.csv");
    record_customer_counts(cafeteria);
    calc_and_show_income(cafeteria);

    print_all_menus(cafeteria);
}
