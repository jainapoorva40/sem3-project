#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global variables
char ch[100];
int v;
int discount=0;

//struct to make linked list of the different coupouns
struct node1{
    char st[100];
    int value;
    struct node1 *next;
};
struct node1 *head = NULL;
struct node1 *last = NULL;

//Check coupon is valid or not and if valid return the value of the coupoun
int checkcoupon(char check[100]){
    struct node1 *temp;
    temp=head;
    while(temp!=NULL){
        if(strcmp(temp->st,check)==0){
            return temp->value;
        }
        temp=temp->next;
    }
    return 0;
}

//This function is only for the admin to add the new coupoun code and their value
void addcoupon(){
    struct node1 *newnode;
    newnode = (struct node1*)malloc(sizeof(struct node1));//memory allocation to the new node
    strcpy(newnode->st,ch);
    newnode->value=v;
    newnode->next=NULL;
    if(head==NULL){
        head=newnode;
        last=newnode;
    }
    else{
        last->next=newnode;
        last=last->next;
    }
}

//This function is used to see all the coupoun offered by resturant
void displaycoupon(){
    struct node1 *temp;
    temp=head;
    while(temp!=NULL){
        printf("\n\t\t\t\t\t\t\t%s\t value=%d",temp->st,temp->value);
        temp=temp->next;
    }
    printf("\n\n");
}

struct node
{
    char foodname[50];
    int quantity;
    float price;
    int data;
    struct node *prev;
    struct node *next;
};

struct node *headc = NULL,*newnode,*tailc = NULL;//making head for the customer
struct node *heada = NULL, *taila = NULL;//making head for the admin
struct node *head_s;

//This function show all the features we provide to the admin of the resturant
void adminmenu()
{
    printf("\n\t\t\t\t\t\t\t1. View total sales\n");
    printf("\t\t\t\t\t\t\t2. Add new items in the order menu\n");
    printf("\t\t\t\t\t\t\t3. Delete items from the order menu\n");
    printf("\t\t\t\t\t\t\t4. Display order menu\n");
    printf("\t\t\t\t\t\t\t5. Add the Coupon code\n");
    printf("\t\t\t\t\t\t\t6. Coupon code\n");
    printf("\t\t\t\t\t\t\t7. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

//This function show all the features we provide to the customer 
void customermenu()
{
    printf("\n\t\t\t\t\t\t\t1. Place your order\n");
    printf("\t\t\t\t\t\t\t2. View your ordered items\n");
    printf("\t\t\t\t\t\t\t3. Delete an item from order\n");
    printf("\t\t\t\t\t\t\t4. Display final bill\n");
    printf("\t\t\t\t\t\t\t5. Back To Main Menu \n\n");
    printf("\t\t\t\t\t\t\t   Enter Your Choice --->");
}

//This function add the new node in the linked of the admin side
struct node* createadmin(struct node *head,int data, char foodname[25], float price)
{
    newnode = (struct node*)malloc(sizeof(struct node));//memory allocated to the new node

    newnode->data = data;
    newnode->price = price;
    newnode-> quantity = 0;
    strcpy(newnode->foodname,foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head;

    if(temp==NULL)
        heada = taila = newnode;
    else
    {
        while(temp->next!=NULL)
            temp=temp->next;

        temp->next=newnode;
        newnode->prev = taila;
        taila = newnode;
    }

    return heada;
}

//This function add the new node in the customer side 
struct node* createcustomer(struct node *head,int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));//memory allocated to the new node

    struct node *temp1 = heada;
    int flag = 0;
    while(temp1!=NULL)
    {
        if(temp1->data==data)
        {
            flag = 1;
            break;
        }
        temp1 = temp1->next;
    }

    if(flag==1)
    {
        newnode->data = data;
        newnode->price = quantity*(temp1->price);
        newnode-> quantity = quantity;
        strcpy(newnode->foodname,temp1->foodname);
        newnode->next = NULL;
        newnode->prev = NULL;

        struct node *temp = head;

        if(temp==NULL)
            headc = tailc = newnode;
        else
        {
            while(temp->next!=NULL)
                temp=temp->next;

            temp->next=newnode;
            newnode->prev = tailc;
            tailc = newnode;
        }


    }
    else
    {
        printf("\n\t\t\t\t\t\t\tThis item is not present in the menu!\n");
    }
    return headc;
}

//this display the list of the food ordered and the quantity
void displayList(struct node *head)
{
    struct node *temp1 = head;
    if(temp1==NULL)
    {
        printf("\n\t\t\t\t\t\t\t\tList is empty!!\n\n");
    }
    else
    {
        printf("\n");
        while(temp1!=NULL)
        {
            if(temp1->quantity==0)
                printf("\t\t\t\t\t\t\t%d\t%s\t%0.2f\n",temp1->data,temp1->foodname,temp1->price);
            else
            {
                printf("\t\t\t\t\t\t\t%d\t%s\t%d\t%0.2f\n",temp1->data,temp1->foodname,temp1->quantity,temp1->price);
            }

            temp1 = temp1->next;
        }
        printf("\n");
    }

}

//This function can be access by the admin , when he wants to see the total items sold and the total sale
struct node* totalsales(int data,int quantity)
{
    newnode = (struct node*)malloc(sizeof(struct node));
    int flag = 0;

    struct node *temp1 = heada;
    while(temp1->data!=data)
    {
        temp1 = temp1->next;
    }

    newnode->data = data;
    newnode->price = quantity*(temp1->price);
    newnode-> quantity = quantity;
    strcpy(newnode->foodname,temp1->foodname);
    newnode->next = NULL;
    newnode->prev = NULL;

    struct node *temp = head_s;

    if(temp==NULL)
        head_s = newnode;
    else
    {
        while(temp->next!=NULL)
        {
            if(temp->data==data)
            {
                flag = 1;
                break;
            }
            temp=temp->next;
        }

        if(flag==1)
        {
            temp->quantity += newnode-> quantity;
            temp->price += newnode->price;
        }
        else
        {
            temp->next=newnode;
        }
    }

    return head_s;
}

//total sale for the resturant
void calculatetotsales()
{
    struct node *temp = headc;
    while(temp!=NULL)
    {
        head_s = totalsales(temp->data, temp->quantity);
        temp=temp->next;
    }
}

//this function is used to delete the food item
struct node* delete(int data,struct node *head, struct node *tail)
{
    if(head==NULL)
    {
        printf("\n\t\t\t\t\t\t\tList is empty\n");
    }
    else
    {
        struct node* temp;
        if(data==head->data)
        {
            temp = head;
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            free(temp);
        }
        else if(data==tail->data)
        {
            temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            free(temp);
        }
        else
        {
            temp = head;
            while(data!=temp->data)
            {
                temp = temp->next;
            }
            (temp->prev)->next = temp->next;
            (temp->next)->prev = temp->prev;
            free(temp);
        }
    }
    return head;
}

//This function is used to delete the food items listed in the menu by the admin
int deleteadmin()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=heada;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            heada = delete(num, heada, taila);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

//This function is used to delete the food item ordered by the customer
int deletecustomer()
{
    printf("\n\t\t\t\t\tEnter serial no. of the food item which is to be deleted: ");
    int num;
    scanf("%d",&num);

    struct node* temp=headc;
    while(temp!=NULL)
    {
        if (temp->data == num)
        {
            headc = delete(num, headc, tailc);
            return 1;
        }
        temp=temp->next;
    }

    return 0;
}

//This function helps to calculate and show the final bill with some functionality(Customer can use Discount Coupon Code , Minimum bill)
void displaybill()
{
    char d[100];
    int cou=0;
    struct node *temp = headc;
    float total_price = 0,total_price1 = 0;
    while (temp!=NULL)
    {
        total_price +=temp->price;
        temp = temp->next;
    }

    printf("\n\t\t\t\t\t\t\t  If you have a discount coupon please press (yes):");
    scanf("%s",d);
    if(strcmp(d,"yes")==0){
        printf("\n\t\t\t\t\t\t\t  Enter the coupon code: ");
        scanf("%s",d);

        //here we call the function to check the coupon validation and the value of the coupon
        cou=checkcoupon(d);
        if(checkcoupon(d)<1){
            printf("\n\t\t\t\t\t\t\t  Invalid coupon code: ");
        }
        else{
            total_price1=(total_price-(total_price*cou)/100);
            discount = discount + ((total_price*cou)/100);
        }
    }
    printf("\n\t\t\t\t\t\t\t  ### Final Bill ###\n");
    displayList(headc);
    if(total_price){
    printf("\t\t\t\t\t\t\tTotal price: %0.02f\n",total_price);
     printf("\t\t\t\t\t\t\tThank you!!!!!!!!!!!!!\n\n");
        printf("\t\t\t\t\t\t\tVisit Again :))\n\n");
    }
    else  //minimum bill
    {total_price=49;
        printf("\t\t\t\t\t\t\tMinimal Price for using our service,you will have to pay %d\n",49);
        printf("\t\t\t\t\t\t\tThank you!!!!!!!!!!!!!\n\n");
        printf("\t\t\t\t\t\t\tVisit Again :))\n\n");
    }
    if(cou>0)
    printf("\n\t\t\t\t\t\t\tTotal price after %d percent discount: %0.02f\n",cou,total_price1);
}


struct node* deleteList(struct node* head)
{
    if(head==NULL)
    {
        return NULL;
    }
    else
    {
        struct node* temp = head;
        while(temp->next!=0)
        {
            temp = temp->next;
            free(temp->prev);
        }
        free(temp);
        head = NULL;
    }

    return head;
}

//this function provide all the function to the admin provided by this project
void admin()
{
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        adminmenu();

        int opt;
        scanf("%d",&opt);

        if(opt==7)
            break;

        switch (opt)
        {
            case 1:
                displayList(head_s);
                printf("\t\t\t\t\t\t\tTotal Discount Given: %d",discount);
                printf("\n");
                break;
            case 2:
                //this case is to add food item in the menu
                printf("\n\t\t\t\t\t\t\tEnter serial no. of the food item: ");
                int num,flag = 0;
                char name[50];
                float price;
                scanf("%d",&num);

                struct node *temp = heada;

                while(temp!=NULL)
                {
                    if(temp->data==num)
                    {
                        printf("\n\t\t\t\t\t\tFood item with given serial number already exists!!\n\n");
                        flag = 1;
                        break;
                    }
                    temp = temp->next;
                }

                if(flag==1)
                    break;

                printf("\t\t\t\t\t\t\tEnter food item name: ");
                scanf("%s",name);
                printf("\t\t\t\t\t\t\tEnter price: ");
                scanf("%f",&price);
                heada = createadmin(heada, num, name, price);
                printf("\n\t\t\t\t\t\t\tNew food item added to the list!!\n\n");
                break;
            case 3:  //this case is to update the menu
                if(deleteadmin())
                {
                    printf("\n\t\t\t\t\t\t### Updated list of food items menu ###\n");
                    displayList(heada);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!\n\n");

                break;
            case 4:
                printf("\n\t\t\t\t\t\t\t   ### Order menu ###\n");
                displayList(heada);
                break;

            case 5:  //this case is to enter the discount coupon code 
                printf("\n\t\t\t\t\t\t\t Enter the coupon code want to insert: ");
                scanf("%s",ch);
                printf("\n\t\t\t\t\t\t\t Enter the value of the coupon code: ");
                scanf("%d",&v);

                addcoupon();
                break;

            case 6:  //this case is to see all the coupon code
                printf("\n\t\t\t\t\t\t\t Available coupon code: ");
                displaycoupon();
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n"); //if admin choose the wrong choice
                break;
        }
    }
}

void customer()
{
    int flag=0,j=1;
    char ch;
    printf("\n\t\t\t\t\t   ----------------------------------------------\n");
    printf("\t\t\t\t\t\t\t    CUSTOMER SECTION\n");
    printf("\t\t\t\t\t   ----------------------------------------------\n");
    while(1)
    {
        customermenu();

        int opt;
        scanf("%d",&opt);

        if(opt==5)
            break;

        switch (opt)
        {
            case 1:
                displayList(heada);   //this case is to offer the customer to order desire food items 
                printf("\n\t\t\t\t\t\tEnter number corresponding to the item you want to order: ");
                int n;
                scanf("%d",&n);
                printf("\t\t\t\t\t\tEnter quantity: ");
                int quantity;
                scanf("%d",&quantity);
                headc = createcustomer(headc, n, quantity);
                break;
            case 2:
                printf("\n\t\t\t\t\t\t\t  ### List of ordered items ###\n");   //this case is to see the odered list by the customer
                displayList(headc);
                break;
            case 3:
                if(deletecustomer())   //this case is to delete the food item from the ordered list
                {
                    printf("\n\t\t\t\t\t\t### Updated list of your ordered food items ###\n");
                    displayList(headc);
                }
                else
                    printf("\n\t\t\t\t\t\tFood item with given serial number doesn't exist!!\n");
                break;
            case 4:
                calculatetotsales();   //this case is to see the bill 
                displaybill();
                headc = deleteList(headc);
                printf("\n\t\t\t\t\t\tPress any key to return to main menu:\n\t\t\t\t\t\t");
                fflush(stdin);
                ch=fgetc(stdin);
                flag=1;
                break;

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");//If wrong functionality is choosen by the customer
                break;
        }
        if(flag==1)
            break;
    }
}

//This function tells the name of the project and tells two types of person login Admin and Customer
void mainnenu()
{
    printf("\n                                 **********\n");
    printf("                                                     WELCOME TO RESTAURANT MANAGEMENT SYSTEM\n");
    printf("                                 **********\n\n\n");
    printf("\t\t\t\t\t\t\t1. ADMIN SECTION--> \n");
    printf("\t\t\t\t\t\t\t2. CUSTOMER SECTION--> \n");
    printf("\t\t\t\t\t\t\t3. Exit--> \n\n");
    printf("\t\t\t\t\t\t\tEnter Your Choice --->");
}

int main()
{
    heada = createadmin(heada,1,"Hot and Sour Soup",100);//by default menu items
    heada = createadmin(heada,2,"Manchow Soup",200);
    heada = createadmin(heada,3,"Manchurian Noodles",150);
    heada = createadmin(heada,4,"Fried Rice",180);
    heada = createadmin(heada,5,"Hakka Noodles",80);

    while(1)
    {
        mainnenu();
        int choice;
        scanf("%d",&choice);

        if(choice==3)
        {
            printf("\n\n\t\t\t\t\t\t\t**Thank you!!**\n");//Exit greeding
            break;
        }

        switch (choice)
        {
            case 1:
                admin();//choice 1 for to login as admin
                break;
            case 2:
                customer();//choice 2 for to login as customer
                break;
            case 3:
                break;//for exit

            default:
                printf("\n\t\t\t\t\t\tWrong Input !! PLease choose valid option\n");
                break;
        }
    }
}