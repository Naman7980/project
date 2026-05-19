#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Max_Users 200
#define length 30
int User_Count = 0;
int product_count = 0;
struct product
{
    char product[50];
    int price;
    char brandname[50];
};
struct product item[Max_Users];
struct person
{
    char name[20];
    int password;
};
struct person users[Max_Users];

struct UserData
{

    char namedata[20];
    int password;
};
struct person data[Max_Users];

int adminVerif(char username[], int password);
void UserWData(int new_index);
void load_users();
void load_items();
void register_user();
void addProduct(void);
void productWFile(int new_product);
void modifyProduct(void);
void adminLogin(void)
{
    char username[50];
    int password;
    int op;

    system("cls");
    printf("\nAdmin login screen");

    printf("\nenter username\n");
    scanf("%s", username);

    printf("\nenter password\n");
    scanf("%d", &password);

    if (adminVerif(username, password) == 0)
    {
        return;
    }

    printf("\n1. view product list");
    printf("\nselect an option\n");
    scanf("%d", &op);

    int p;
    switch (op)
    {
    case 1:

        printf("\n1. Add product");
        printf("\n2. Modify product\n");
        scanf("%d", &p);

        switch (p)
        {
        case 1:
            addProduct();
            break;

        case 2:
            modifyProduct();
            break;
        default:
            printf("\nerror! invalid option");
            return;
            break;
        }
        break;

    default:
        printf("\nerror! invalid option");
        return;
        break;
    }

    int n;
    printf("\npress 0 to return: ");
    scanf("%d", &n);
    if (n == 0)
    {
        return;
    }
}
void userLogin(void)
{
    char username[50];
    int password;
    int op;

    system("cls");
    printf("\nUser login screen");

    printf("\nenter username\n");
    scanf("%s", username);

    printf("\nenter password\n");
    scanf("%d", &password);

    int found = 0;

    for (int i = 0; i < User_Count; i++)
    {
        if (strcmp(users[i].name, username) == 0 && users[i].password == password)
        {
            found = 1;
            break;
        }
    }

    if (found)
    {
        printf("\nLogin successful!\n");

       printf("\n<this is the product list>\n");
        for (int j = 0; j < sizeof(product_count); j++)
        {
            printf("\nproduct no: %d", j + 1);
            printf("\nproduct name: %s", item[j].product);
            printf("\nproduct price: %d", item[j].price);
            printf("\nproduct brandname: %s\n", item[j].brandname);
        } 
    }
    else
    {
        printf("\nInvalid credentials!\n");
    }

    int n;
    printf("\npress 0 to return");
    scanf("%d", &n);

    if (n == 0)
    {
        return;
    }
}

int main()
{
    FILE *fp = fopen("admin.bin", "wb");

    struct person admin = {"admin", 1234};

    fwrite(&admin, sizeof(struct person), 1, fp);

    fclose(fp);

    load_users();
    load_items();

    system("cls");
    int op, n;
    while (1)
    {
        printf("\n[Quick^buys]");
        printf("\n1. Admin login");
        printf("\n2. User login");
        printf("\n3. Exit...");
        printf("\nchoose an option: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            adminLogin();
            break;

        case 2:

            while (1)
            {
                printf("\n1. login user");
                printf("\n2. register user");
                printf("\n3. exit.\n");
                scanf("%d", &n);
                switch (n)
                {
                case 1:
                    userLogin();
                    break;

                case 2:
                    register_user();
                    break;

                case 3:
                    return 0;
                    break;
                default:
                    printf("error! invalid option");
                    exit(0);
                    break;
                }
            }

            break;

        case 3:
            printf("\nExiting the program...");
            exit(0);
            break;
        default:
            printf("\nerror!! invalid option returning...");
            return 0;
            break;
        }
    }

    return 0;
}
int adminVerif(char username[], int password)
{
    FILE *infile = fopen("admin.bin", "rb");

    if (infile == NULL)
    {
        fprintf(stderr, "Error opening file\n");
        return 0;
    }

    struct person input1;

    fread(&input1, sizeof(struct person), 1, infile);

    fclose(infile);

    if (strcmp(input1.name, username) == 0 && input1.password == password)
    {
        printf("\nlogin sucessful!!\n");
        return 1;
    }
    else
    {
        printf("\nerror!! login\n");
        return 0;
    }
}
void register_user()
{
    int new_index = User_Count;

    system("cls");
    printf("\nUser register screen");

    printf("\nregister a new user");
    printf("\nenter username: ");
    scanf("%29s", users[new_index].name);

    printf("\nenter password: ");
    scanf("%d", &users[new_index].password);

    for (int i = 0; i < new_index; i++)
    {
        if (strcmp(users[new_index].name, users[i].name) == 0)
        {
            printf("error! the username is already exist please try another one");
            return;
        }
    }

    UserWData(new_index);

    User_Count++;

    printf("user registered sucessfully");

    int n;
    printf("\npress 0 to return");
    scanf("%d", &n);

    if (n == 0)
    {
        return;
    }
}

void UserWData(int new_index)
{
    FILE *outfile = fopen("Userdata.bin", "ab");

    if (outfile == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    fwrite(&users[new_index], sizeof(struct person), 1, outfile);

    fclose(outfile);
}
void load_users()
{
    FILE *infile = fopen("Userdata.bin", "rb");

    if (infile == NULL)
        return;

    User_Count = 0;

    while (fread(&users[User_Count], sizeof(struct person), 1, infile))
    {
        User_Count++;
        if (User_Count >= Max_Users)
            break;
    }

    fclose(infile);
}
void addProduct(void)
{
    int new_product = product_count;

    system("cls");

    printf("\nAdd product list");

    printf("\nAdd a new product");

    printf("\nEnter product name\n");
    scanf("%s", item[new_product].product);

    printf("\nEnter product price\n");
    scanf("%d", &item[new_product].price);

    printf("\nEnter product bramd\n");
    scanf("%s", item[new_product].brandname);

    productWFile(new_product);
    product_count++;

    printf("product registered sucessfully");

    int n;
    printf("\npress 0 to return: ");
    scanf("%d", &n);

    if (n == 0)
    {
        return;
    }
}
void productWFile(int new_product)
{
    FILE *profile = fopen("product.bin", "ab");

    if (profile == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    fwrite(&item[new_product], sizeof(struct product), 1, profile);

    fclose(profile);
}
void load_items()
{    FILE *itemfile = fopen("product.bin", "rb");

    if (itemfile == NULL)
        return;

    product_count = 0;

    while (fread(&item[product_count], sizeof(struct product), 1, itemfile))
    {
        product_count++;
        if (product_count >= Max_Users)
            break;
    }

    fclose(itemfile);
}
void modifyProduct(void)
{
    char findproduct[20];
    char findbrand[50];
    int c = 0;

    printf("\nEnter product name\n");
    scanf("%s", findproduct);

    for (int i = 0; i < product_count; i++)
    {
        if (strcmp(item[i].product, findproduct) == 0)
        {
            c++;
            for (int j = 0; j < c; j++)
            {
                printf("\n%d option", j + 1);
                printf("\nproduct price: %d", item[j].price);
                printf("\nproduct brand name: %s\n", item[j].brandname);
            }
        }
    }
    printf("\nenter product brand name\n");
    scanf("%s", findbrand);

    for (int k = 0; k < c; k++)
    {

        for (int l = 0; l < product_count; l++)
        {
            if (strcmp(item[l].brandname, findbrand) == 0)
            {
                printf("\nenter product new price\n");
                if (scanf("%d", &item[l].price))
                {
                    printf("\nproduct price modify sucessfully");
                    break;
                }
            }
        }
    }

    int n;

    printf("\n1. add product");
    printf("\n2. modify product");
    printf("\n3. exit...\n");
    printf("\nselect an option\n");

    scanf("%d", &n);

    switch (n)
    {
    case 1:
        addProduct();
        break;

    case 2:
        modifyProduct();
        break;

    case 3:
        return;
        break;

    default:
        printf("\nerror!! invalid option returning...");
        return;
        break;
    }
}
// i worked in this code for 1 week still i cant complete it all