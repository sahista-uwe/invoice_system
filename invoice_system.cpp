#include <iostream> //basic input and output
#include <fstream> //file handeling
#include <string> //strings input
#include <sstream> //reading and writing strings
#include <stdlib.h> //provides access to functionalities
using namespace std;

const int MAX_PRODUCTS = 1000; // Maximum number of products that can be handled in the program
const int MAX_CUSTOMERS = 1000;// Maximum number of customer that can be handled in the program
const int MAX_INVOICES = 1000;// Maximum number of invoices that can be handled in the program

/* Base class for products. All data members are protected so that they 
   can be accessed and modified in derived classes such as Electronic, Clothing, Groceries, and Book. */
class Product {
    protected:
    int productID;  // Unique identifier for the product
    string productName;  // Name of the product
    double productPrice;  // Price of the product
    int productQuantity;  // Available stock quantity of the product

    public:
   // Default constructor initializing member variables with default values
    Product() : productID(0), productName(""), productPrice(0), productQuantity(0){}

     // Parameterized constructor to initialize a product with specific values
    Product ( int id, string name, double price, int quantity) 
    : productID(id), productName(name), productPrice(price), productQuantity(quantity){}

   // Getter methods to provide access to private/protected members outside the class
    int getproductID(){return productID;}
     string getproductName(){return productName;}
     double getproductPrice(){return productPrice;}
     int getproductQuantity(){return productQuantity;}

  /* Method to decrease the product quantity when purchased.
       Returns true if the stock is successfully updated; false otherwise. */
    bool decreaseQuantity(int purchasedQuantity) {\
        if(purchasedQuantity <= productQuantity){
            productQuantity = productQuantity - purchasedQuantity; // Reduce stock
            return true; // Stock successfully decreased
        }else{ 
             // Insufficient stock
            cout <<"Not enought stock available for product:" <<productName <<endl;
        return false;
        }
        }

    /* Virtual method to be overridden in derived classes.
       Calculates the total price (default is the base price of the product). */
    virtual double totalPrice() const {
    return productPrice;
    }
   
     /* Virtual method to display product details.
       This can be overridden in derived classes to include additional details. */
    virtual void displayProduct() const {
        cout <<"=========================================="<<endl;
        cout <<"--------------Product ID: " <<productID <<endl;
        cout <<"------------Product Name: " <<productName <<endl; 
        cout <<"-------------------Price: " <<productPrice  <<endl;
        cout <<"--------Product Quantity: " <<productQuantity <<endl;
        cout <<"=========================================="<<endl;
        cout <<endl;
     }
 // Virtual destructor for proper memory management in case of polymorphic usage
  virtual ~Product(){}
};


// Derived class of Product, specifically for Electronic products
class Electronic : public Product {
    private:
    int warrantyyears; // The warranty period for the electronic product (in years)

    public:
    // Default constructor, initializing warranty years to 0
    Electronic() : warrantyyears(0){}

   
    /* Parameterized constructor for initializing an Electronic product with its
       ID, name, price, quantity, and warranty years. It calls the base class constructor for product details. */
    Electronic (int id, string name, double price, int quantity, int years) 
    : Product (id, name, price, quantity), warrantyyears (years) {}

    /* Override of the totalPrice method from the base Product class.
       Currently, it returns only the base price of the product,
       but can be modified to include additional cost based on warranty. */
    double totalPrice() const override {
        double warrantyCost = productPrice* (warrantyyears*0.05);
    return productPrice + warrantyCost;
    }


      /* Override of the displayProduct method to display additional information specific to Electronic products,
       such as warranty years. */
     void displayProduct() const override {
        cout <<"=========================================="<<endl;
        cout <<"--------------Product Id: " <<productID<<endl;
        cout <<"------------Product Name: " <<productName <<endl;
        cout <<"-----------Product Price: " <<productPrice <<endl;
        cout <<"--------Product Quantity: " <<productQuantity <<endl;
        cout <<"--Product Warranty Years: " <<warrantyyears <<endl;
        cout <<"=========================================="<<endl;
        cout <<endl;

    }
};


// Derived class of Product, specifically for Clothing products
class Clothing : public Product  {
    private:
    string size; // The size of the clothing item (e.g., Small, Medium, Large)


    public:
    // Default constructor, initializing size to an empty string
    Clothing() : size(""){}

     // Parameterized constructor for initializing a Clothing product with its
    // ID, name, price, quantity, and size. It calls the base class constructor for product details.
    Clothing(int id, string name, double price, int quantity, string itemsize)
    : Product(id, name, price, quantity), size(itemsize) {}

    // Override of the totalPrice method from the base Product class.
    // Currently, it returns only the base price of the product.
    double totalPrice() const override {
      double sizeCost = 0.0;

        // Price adjustment based on size
        if (size == "Large") {
            sizeCost = productPrice * 0.1; // 10% increase for Large size
        } else if (size == "Medium") {
            sizeCost = productPrice * 0.05; // 5% increase for Medium size
        } else if (size == "Small") {
            sizeCost = productPrice * 0.02; // 2% increase for Small size
        }
        return productPrice + sizeCost;
    }

  // Override of the displayProduct method to display additional information specific to Clothing products,
    // such as size.
    void displayProduct() const override {
        cout <<"=========================================="<<endl;
        cout <<"---------------Product Id: " <<productID <<endl;
        cout <<"-------------Product Name: " <<productName <<endl;
        cout <<"------------Product Price:  " <<productPrice <<endl;
        cout <<"---------Product Quantity: " <<productQuantity <<endl;
        cout <<"-------------Product Size: " <<size <<endl;
        cout <<"=========================================="<<endl;
        cout <<endl;
    }

};


// Derived class of Product, specifically for Groceries
class Groceries : public Product  {
    private:
    double weight; // Weight (in kg or L) of the grocery product


    public:
    // Default constructor, initializes weight to 0
    Groceries(): weight(0){}

    // Parameterized constructor to initialize product details and weight
    Groceries(int id, string name,double price, int quantity, double kgweight )
    : Product (id, name, price, quantity), weight(kgweight){}
    

    // Override of the totalPrice method to calculate price based on weight
    double totalPrice() const override{
        return productPrice*weight; // Total price = price per unit * weight
    }
    // Override of the displayProduct method to display product-specific info
    void displayProduct() const override {
        cout <<"=========================================="<<endl;
        cout <<"-----------------Product Id: " <<productID <<endl;
        cout << "--------------Product Name: " <<productName <<endl;
        cout <<"--------------Product Price: " <<productPrice <<endl;
        cout <<"-----------Product Quantity: " <<productQuantity <<endl;
        cout <<"---------------Weight/Litre: " << weight <<endl;
        cout <<"=========================================="<<endl;
        cout <<endl;
    }

};


// Derived class of Product, specifically for Book products
class Book : public Product {
    private:
    string bookName; // Name of the book
    string genre;    // Genre of the book (e.g., Fiction, Non-fiction, etc.)

    public:
// Default constructor, initializes bookName and genre to empty strings
    // This ensures that when a Book object is created without parameters, these fields are safely initialized.
        Book() : bookName(""), genre(""){}

// Parameterized constructor, initializes product details and book-specific attributes
    // It calls the base class constructor for initializing product details like ID, price, and quantity.
        Book(int id, string name, double price, int quantity, string bname, string bgenre)
    : Product(id, name, price, quantity), bookName(bname),genre(bgenre){}

// Overridden totalPrice() method to return the price of a single book
    double totalPrice() const override {
        return productPrice; // Returns the price for one book
    }

// Overridden displayProduct() method to display all the details of the book
    // It calls the base class method for displaying common product details and adds book-specific information.
        void displayProduct() const override {
        cout <<"=========================================="<<endl;
        cout <<"---------------Product Id: " <<productID <<endl;
        cout <<"-------------Product Name: " <<productName <<endl;
        cout <<"------------Product Price:  " <<productPrice <<endl;
        cout <<"---------Product Quantity: " <<productQuantity <<endl;
        cout <<"----------------Book Name: " <<bookName <<endl;
        cout <<"--------------------Genre: " <<genre <<endl;
        cout <<"=========================================="<<endl;
        cout <<endl;
    }
};

/* Class of Customer: All data members are protected to allow inheritance in child classes:
Invoice, CustomerManager, etc. This class manages basic customer details. */
class Customer{

    protected:
    int customerID; // Customer's unique ID
    string customerName; // Customer's name
    string contactPhone;  // Customer's contact phone number
   
    public:
 // Default constructor: Initializes customerID to 0, customerName and contactPhone to empty strings
    // This ensures that an object of the Customer class is properly initialized with default values.
    Customer() : customerID(0), customerName(""), contactPhone(""){}

  // Parameterized constructor: Initializes customer details with specific values
    // It allows initialization of customerID, customerName, and contactPhone from the constructor arguments.
    Customer(int cid, string name, string phone)
    :customerID(cid), customerName(name), contactPhone(phone){}

     // Getter for customerID: Provides access to the customer's ID outside the class
    // This method allows other classes or functions to retrieve the unique ID of the customer.
    // This method allows retrieval of the customer's name.
    // This method allows retrieval of the customer's contact phone number.

    int getcustomerID(){return customerID;}
    string getcustomerName(){return customerName;}
    string getconctactPhone() {return contactPhone;}

// Displays customer information: Prints the customer details in a formatted manner
    // This method outputs customerID, customerName, and contactPhone to the console for display purposes.
        void displayCustomer() const {
        cout <<"=========================================="<<endl;
        cout <<"------------------Customer Id: " <<customerID <<endl;
        cout <<"----------------Customer Name: " <<customerName <<endl;
        cout <<"----------------Customer Info: " <<contactPhone <<endl;
        cout <<"=========================================="<<endl;
        cout <<endl;
    }
     // Virtual destructor: Ensures proper cleanup of derived classes (if any) that are dynamically allocated
    // This destructor can be overridden in derived classes to clean up any additional resources.
    virtual ~Customer(){}

};


/* Base class of Invoice: All data members are protected to allow inheritance in derived classes like:
Customer, InvoiceManager, etc. This class manages basic invoice operations. */
class Invoice {

    protected:
    int invoiceID;       // Unique identifier for the invoice
    double totalAmount;  // Total amount of the invoice (calculated)
    int productCount;      // Number of products in the invoice
    int invoiceCount;       // Number of invoices created 

    // Structure to store product and its purchased quantity
    struct ProductEntry {
       Product* product;       // Pointer to a Product object
        int purchasedQuantity;    // Quantity of the product purchased
    };
    
    ProductEntry products[MAX_PRODUCTS];                // Array of ProductEntry, stores products in the invoice
    Invoice* invoices[MAX_INVOICES];                   // Array of Invoice pointers 

    public:
    // Default constructor: Initializes invoiceID to 0, productCount to 0, and invoiceCount to 0
    // Ensures that an Invoice object is properly initialized with default values.
    Invoice() : invoiceID(0), productCount(0) ,invoiceCount(0){}

    // Parameterized constructor: Initializes invoiceID with a given value, productCount and invoiceCount to 0
    Invoice(int iid) : invoiceID(iid), productCount(0), invoiceCount(0){} 

    // Getter for invoiceID: Provides access to the invoice's ID outside the class
    int getinvoiceID() const {return invoiceID;}


    // Adds a product to the invoice by storing it in the products array with the given quantity
     void addProduct(Product* product, int quantity){
            if(productCount < MAX_PRODUCTS) {
           products[productCount] = {product, quantity};  // Adds product and quantity to the list
            productCount++;                              // Increment productCount to keep track of the number of products in the invoice
        } else { 
            cout <<"Sorry! Cannot add more products" <<endl;      // Limits to the max number of products
        }
    }
    

    // Calculates the total amount for the invoice by iterating through all products and summing their total price
    double caltotalAmount() {
        totalAmount = 0;
        for (int i=0; i<productCount; i++ ){
            totalAmount += products[i].product->totalPrice() * products[i].purchasedQuantity; 
            // Adds to totalAmount by calling totalPrice() method from each product
        }
        return totalAmount;
    }

    // Displays the invoice, including product details and total amount
      void displayInvoice(){
        cout <<endl;
        cout <<endl;
        cout <<"======================================" <<endl;;
        cout <<"       MY DEPARTMENT STORE" <<endl;    
        cout <<"         INVOICE # " <<invoiceID <<endl;
        cout <<"--------------------------------------" <<endl;
        cout <<"Product Details: " <<endl;
       cout <<"SN "<< "ProductID " <<"Particulars " <<"Rate " <<"Qty " <<endl;

        for (int i=0; i<productCount; i++){
            cout << i+1 <<"\t"
            <<products[i].product->getproductID()  <<"\t"
             <<products[i].product->getproductName() <<"\t"
             <<products[i].product->getproductPrice() <<"\t"
             <<products[i].purchasedQuantity <<endl; 
                     }
        cout <<"--------------------------------------" <<endl;
        cout <<"Total Amount: Rs "<< caltotalAmount() <<endl;
        cout <<"--------------------------------------"<<endl;   
        cout <<"========Thank You For Shopping========" <<endl;
        cout <<endl;
    }

    // Saves the invoice details to a file
    void saveToFile(ofstream& invoiceFile) {
    invoiceFile <<"--------------------------------------" <<endl;
    invoiceFile <<"     MY DEPARTMENT STORE" <<endl;    
    invoiceFile <<"------------------------------"<<"\n";
    invoiceFile <<"Invoice ID: " << invoiceID << endl;
    invoiceFile <<"Product Number: " << productCount << endl;
    invoiceFile <<"------------------------------"<<"\n";
    
    // Iterates through all products in the invoice and saves their details to the file
    for (int i = 0; i < productCount; i++) {
        invoiceFile <<"Product ID: " << products[i].product->getproductID() << endl;
        invoiceFile <<"Product Name: " << products[i].product->getproductName() << endl;
        invoiceFile <<"Product Price: "<< products[i].product->getproductPrice() << endl;
        invoiceFile <<"Purchase Quantity: " <<products[i].purchasedQuantity <<endl; 
    }
    invoiceFile <<"------------------------------"<<"\n";

    invoiceFile <<"Total Amount: Rs. " << caltotalAmount() << endl;  // Calculates the total amount dynamically
    invoiceFile <<"========Thank You For Shopping========" <<endl;

}


// Destructor for proper memory management: Deletes products in the invoice
    // Ensures that dynamically allocated memory (Product objects) is properly freed.
        ~Invoice(){ 
        for(int i = 0; i<productCount; i++){
            delete products[i].product;       // Deletes each dynamically allocated Product object in the invoice
        }
    }
};


// Class for managing products, derived from Product class
class ProductManager{

    private:
    int productCount;       // Variable to track the number of products in the manager
    Product* products[MAX_PRODUCTS];       // Array to store pointers to Product objects

    public:
    // Default constructor: Initializes productCount to 0
    ProductManager() : productCount(0) {}

    // Adds a product to the manager and tracks the count
    void addProduct(Product* product) {
        // Check if product already exists in memory by product ID
        if (productSearch(product->getproductID())!=nullptr){
            cout <<"PRODUCT ALREADY EXITS CHECKED BY PRODUCT ID!"<<endl;
            return; // Exit function if product already exists
        }
         // Check if product already exists in the file by product ID
        if (productSearchInFile(product->getproductID())) {
            cout << "PRODUCT ALREADY EXISTS IN FILE CHECKED BY PRODUCT ID!" << endl;
            return;   // Exit function if product exists in file
        }
                    // If space is available, add the product to the products array and increase the count
        if(productCount < MAX_PRODUCTS) {
           products[productCount] = product; // Add product to array
            productCount++;
            cout <<"Product added successesfully, Press(2) to save in File." <<endl;
        } else {
             // If the product array is full, display an error message
            cout <<"Sorry! Can not add more products or Product already exits!" <<endl;
        }
    }
    

    // Searches for a product by product ID in memory
    Product* productSearch (int searchID){
                // Loop through all products and return the product if ID matches
        for (int i=0; i<productCount; i++){
            if(products[i]->getproductID() == searchID){
                return products[i];  // Return the found product
            }
        }
        return nullptr;    // Return nullptr if product not found
    }

    // Saves all products in memory to a file
  void saveProductsToFile() {
            // Open the file in append mode
    ofstream productFile("products.txt", ios::app);  // Open file for writing
    if (!productFile) {
        cout << "Error opening file to save products!" << endl;
        return; // Return if the file could not be opened
    }

              // Loop through all products and save to the file
    for (int i = 0; i <productCount; i++) {
        Product* product =products[i];
         // Check if the product already exists in the file before appending
            if (productSearchInFile(product->getproductID())) {
                cout << "Product ID " << product->getproductID() << " already exists in file, skipping saving." << endl;
                continue;  // Skip saving this product if it already exists in file
            }

        productFile <<"-------------------------------------------------" <<"\n"
                    <<"Product ID: "<< product->getproductID() <<"\n"
                    << "Product Name: " <<product->getproductName()  <<"\n"
                    << "Product Price: " <<product->getproductPrice() <<"\n"
                    << "Product Quantity: " <<product->getproductQuantity() <<endl;
    }

    productFile.close();  // Close the file after writing
    cout << "Product information saved to file." << endl;
}
// Checks if a product with a specific ID exists in the file
    bool productSearchInFile(int searchID) {
        // Open the file in read mode
        ifstream productFile("products.txt");  // Open file for reading
        if (!productFile) {
            cout << "Error opening file to load products!" << endl;
            return false; // Return false if file could not be opened
        }

        string line;
        while (getline(productFile, line)) {         
            // Loop through each line in the file and search for the product ID
            if (line.find("Product ID: " + to_string(searchID)) != string::npos) {
                productFile.close(); // Close the file after finding the product
                return true;  // Product found in the file
            }
        }

        productFile.close();  // Close the file after reading
        return false;  // Product not found in the file
    }

    // Loads product information from the file into memory
void loadProductsFromFile() {
        // Open the file in read mode
    ifstream productFile("products.txt");  // Open file for reading
    if (!productFile) {
        cout << "Error opening file to load products!" << endl;
        return; // Return if the file could not be opened
    }

    string line;
            // Loop through each line in the file and load product details
    while (getline(productFile, line)) {
        stringstream ss(line);
        int productID;
        string productName;
        double productPrice;
        int productQuantity;
        int purchasedQuantity;

        // Parse the product details from the line
        if (getline(ss, productName, ',')&& //get name, id, price and ignore comma
             ss>> productID && ss.ignore() && 
             ss>> productPrice && ss.ignore() &&
             ss>> productQuantity && ss.ignore() &&
             ss>>purchasedQuantity) {
                                
            // If product does not exist in memory, create a new product and add it
                if (productSearch(productID) == nullptr){
            Product* product = new Product (productID, productName, productPrice,productQuantity);
            addProduct(product);  // Add the product to memory
                }
        }
   cout <<line <<" " <<endl; // Display the line for debugging purposes
    }
    productFile.close();  // Close the file after reading
    cout << "Product information loaded from file." << endl;
}

// Destructor: Frees memory by deleting all dynamically allocated products
    ~ProductManager(){
                // Loop through all products and delete them to free memory
        for (int i= 0; i<productCount; i++){
            delete products[i];
        }
    }
};


// CustomerManager class: A class responsible for managing customer data
class CustomerManager {

    private:
    int customerCount; // Keeps track of the number of customers
    Customer* customers[MAX_CUSTOMERS]; // Array to hold pointers to customer objects

    public:
    // Default constructor initializing customerCount to 0
    CustomerManager(): customerCount(0){}

    // Adds a new customer to the customer list
    void addCustomer(Customer* customer){  // Check if the customer already exists by customer ID
        if(customerSearch(customer->getcustomerID())!=nullptr){
            cout <<"CUSTOMER ALREADY EXITS CHECKED BY CUSTOMER ID! "<<endl;
            return; // If the customer already exists, return without adding
        }
        // Check if the customer already exists in the file by customer ID
        if (customerSearchInFile(customer->getcustomerID())) {
            cout << "CUSTOMER ALREADY EXISTS IN FILE CHECKED BY CUSTOMER ID!" << endl;
            return; // If the customer exists in the file, return without adding
        }
        // If there's space in the customers array, add the customer
        if(customerCount < MAX_CUSTOMERS){
            customers[customerCount] = customer; // Store the customer in the array
            customerCount++; // Increment the customer count
            cout <<"Customer added successesfully, Press (5) to save in File." <<endl;
        }else{
            cout <<"Sorry! Can not add more customers"<<endl; // If the array is full, display an error
        }
    }

    //Searching customer by id of customer
    Customer* customerSearch (int searchID){
        for ( int i=0; i <customerCount; i++){
            if (customers[i]->getcustomerID() == searchID ) {
                return customers[i]; // Return the customer if found
            }
        } return nullptr;  // Return nullptr if the customer is not found
    }
    // Saves customer information to a file
    void saveCustomersToFile(){
        ofstream customerFile ("customers.txt", ios::app); // Open file to write customer data
        if(!customerFile){
            cout <<"Error opening file to save customers!"<<endl;
            return; // If the file cannot be opened, return without saving
        }
         // Iterate over all customers and save their data to the file
        for (int i=0; i<customerCount; i++) {
            Customer* customer= customers[i];
             // Check if the customer already exists in the file before appending
            if (customerSearchInFile(customer->getcustomerID())) {
                cout << "Customer ID " << customer->getcustomerID() << " already exists in file, skipping saving." << endl;
                continue; // Skip saving this customer if it already exists in file
            }
            // Write the customer's details to the file
            customerFile <<"----------------------------------------------" <<"\n"
                        <<"Customer ID: " <<customer->getcustomerID() <<endl
                         <<"Customer Name: "<< customer->getcustomerName() <<endl
                         <<"Customer Phone No.: " <<customer->getconctactPhone() <<endl;
        }
        customerFile.close(); // Close the file after writing
        cout<<"Customer information saved in file. "<<endl;
    }

  // Checks if a customer with a specific ID exists in the file
    bool customerSearchInFile(int searchID) {
        ifstream customerFile("customers.txt"); // Open file for reading
        if (!customerFile) {
            cout << "Error opening file to load customers!" << endl;
            return false; // Return false if file could not be opened
        }

        string line;
        // Loop through each line in the file and search for the customer ID
        while (getline(customerFile, line)) {
            // Loop through each line in the file and search for the customer ID
            if (line.find("Customer ID: " + to_string(searchID)) != string::npos) {
                customerFile.close(); // Close the file after finding the customer
                return true; // Customer found in the file
            }
        }

        customerFile.close(); // Close the file after reading
        return false; // Customer not found in the file
    }
    
    // Loads customer data from a file and adds it to the customer list
    void loadCustomersFromFile(){
        ifstream customerFile("customers.txt");  // Open file for reading
        if(!customerFile){
            cout <<"Error opening file to load products! "<<endl;
            return; // If the file cannot be opened, return without loading
        }
        string line;
        while(getline(customerFile, line)){
            stringstream ss(line);
            int customerID;
            string customerName;
            string contactPhone;
            
              // Parse the customer data from the file
            if(getline(ss, customerName, ',') &&
                ss>> customerID && ss.ignore() &&
                ss>> contactPhone) {
                    // If the customer does not already exist in the system, add them
                    if(customerSearch(customerID)== nullptr){
                        Customer* customer = new Customer (customerID, customerName, contactPhone);
                        addCustomer(customer);
                    }
                }
                cout  <<line <<" " <<endl; // Display
        }
        customerFile.close(); // Close the file after reading
        cout<<"Customer information loaded from File." <<endl;
    }
  
    // Destructor for proper memory management (frees up allocated memory for customers)
    ~CustomerManager(){
        for(int i = 0; i< customerCount; i++){
            delete customers[i]; // Delete each customer object to prevent memory leaks
        }
    }
}; 


/* Class of InvoiceManager, derived class of Invoice */
class InvoiceManager : public Invoice {

private:
int invoiceCount;                 // Keeps track of the number of invoices added
Invoice* invoices[MAX_INVOICES];  // Array to store pointers to invoices

public:
// Default constructor initializes invoiceCount to 0
InvoiceManager() : invoiceCount(0) {}


    // Adds invoices to the manager and counts the invoices added
    void addInvoice(Invoice* invoice){
        // Check if the invoice with the same ID already exists in the system
    if(invoiceSearch(invoice->getinvoiceID())!=nullptr){
        cout <<"INVOICE ALREADY EXITS CHECKED BY INVOICE ID!"<<endl;
        return;
    }

    // Now check in the file (using invoiceExistsInFile)
    if (invoiceExistsInFile(invoice->getinvoiceID())) {
        cout << "INVOICE ALREADY EXISTS IN FILE!" << endl;
        return;
    }

    // Check if there is space to add more invoices
    if(invoiceCount < MAX_INVOICES){
        invoices[invoiceCount] = invoice;
        invoiceCount++;
        cout <<"Invoice Added successfully, Press(8) to save in file."<<endl;
    }else {
             // If the limit of invoices is reached
        cout <<"Sorry! Cannot add more invoices"<<endl;
    }
    }


// Searching invoices by invoice ID
Invoice* invoiceSearch(int searchID){
            // Loop through all invoices to find a match
    for ( int i=0; i<invoiceCount; i++){
        if(invoices[i]->getinvoiceID() == searchID){
            return invoices[i];  // Return the matching invoice pointer
        }
    }
    return nullptr;    // Return null if invoice is not found
}
    
    // Save all invoices to a file, avoiding duplicates
void saveInvoicesToFile() {
    // Open the file in output mode (it overwrites the file if it exists)
    ofstream invoiceFile("invoices.txt", ios::app); // Open in append mode to avoid overwriting
    if (invoiceFile.is_open()) {
        // Loop through all invoices in the manager
               for (int i = 0; i < invoiceCount; i++) {
                // Before saving, check if the invoice already exists in the file
                if (!invoiceExistsInFile(invoices[i]->getinvoiceID())) {
                    invoices[i]->saveToFile(invoiceFile);   // Save invoice details to file
                } else {
                    cout << "Invoice with ID " << invoices[i]->getinvoiceID() << " already exists in the file!" << endl;
                }
            }
            invoiceFile.close();    // Close the file after writing
            cout << "Invoice information saved in file." << endl;
        } else {
                        // Error handling if the file can't be opened
            cout << "Error opening file for saving invoices!" << endl;
        }
    }

    // Check if an invoice with a specific ID already exists in the file
    bool invoiceExistsInFile(int searchID) {
        ifstream readFile("invoices.txt");
                // Open the file in read mode
        if (!readFile.is_open()) {
            cout << "Error opening the file for reading!" << endl;
            return false; // Return false if file can't be opened
        }

        string line;
                // Read the file line by line
        while (getline(readFile, line)) {
            // Check if the line contains the invoice ID
            if (line.find("Invoice ID: " + to_string(searchID)) != string::npos) {
                readFile.close(); // Close the file after reading
                return true;    // Return true if invoice ID is found
            }   
        }

        readFile.close();  // Close the file if no match is found
        return false;  // Return false if invoice ID is not found
    }

    // Destructor for proper memory management (deletes dynamically allocated invoices)
    ~InvoiceManager(){
        for(int i = 0; i< invoiceCount; i++){
            delete invoices[i];   // Delete each dynamically allocated invoice
        }
    }
};


int main() {

    // Instantiate managers for handling products, customers, and invoices
    ProductManager productManager;
    CustomerManager customerManager;
    InvoiceManager invoiceManager;
    

    int option;
    // Start of menu loop

    do {
        // Display the menu to the user
        cout <<"========================================" <<endl;
        cout <<"----Welcome to the Department Store!----" <<endl;
        cout <<"1. Add & Display Product: " <<endl;
        cout <<"2. Save Products in File: " <<endl;
        cout <<"3. Display Products from File: " <<endl;
        cout <<"----------------------------------------"<<endl;

        cout <<"4. Add & Display Customer: " <<endl;
        cout <<"5. Save Customers in File: " <<endl;
        cout <<"6. Display Customers from File: " <<endl;
        cout <<"----------------------------------------"<<endl;

        cout <<"7. Create & Display Invoice: " <<endl;
        cout <<"8. Save Invoice in File: " <<endl;
        cout <<"----------------------------------------"<<endl;

        cout <<"9. Search for product by Product ID: " <<endl;
        cout <<"10. Search for customer by Customer ID: " <<endl;
        cout <<"11. Search for invoice by Invoice ID: " <<endl;
        cout <<"----------------------------------------"<<endl;

        cout <<"12. Exit! : " <<endl;
        cout <<"========================================" <<endl;


        // Prompt the user to select an option
        cout <<"Enter your option from 1-12: "<<endl;
        cin >> option;
        // Switch case for handling different options
        switch(option){
            case 1: {// Add and display product
                int productID, quantity, warrantyyears;
                string productName, size, genre, bookName;
                double price, weight;
                // Input product details from the user
                cout <<"Enter Product ID: "<<endl;
                cin >>productID;
                cout <<"Enter the Product Name:"<<endl;
                cin.ignore();  // To discard unwanted data
                getline(cin, productName); // To take entire input
                cout <<"Enter Product Price: " <<endl;
                cin >>price;
                cout <<"Enter Product Quantity: " <<endl;
                cin >>quantity;
                // Select product type and take relevant input
                cout <<"Select Product Type: "<<endl;
                cout <<"1. Electronic: " <<endl;
                cout <<"2. Clothing (Large/Medium/Small): " <<endl;
                cout <<"3. Groceries: " <<endl;
                cout <<"4. Book: " <<endl;

                int productType;
                cin>> productType;

                // Create product object based on the selected type
                if (productType == 1){ //electronic
                cout <<"Enter the warranty years: "<<endl;
                cin >>warrantyyears;

                Electronic* productElectronic = new Electronic (productID,productName, price, quantity, warrantyyears);
                productManager. addProduct (productElectronic);
                productElectronic->displayProduct();

                } else if(productType == 2){ //clothing
                cout <<"Enter the size of clothe: " <<endl;
                cin >>size;

                Clothing* productClothing = new Clothing(productID, productName, price, quantity, size);
                productManager.addProduct(productClothing);
                productClothing->displayProduct();

                }else if (productType == 3){ // groceries
                cout <<"Enter the Weight in kg: " <<endl;
                cin >>weight;

                Groceries* productGroceries = new Groceries (productID, productName, price, quantity, weight );
                productManager.addProduct(productGroceries);
                productGroceries->displayProduct();

                }else if (productType == 4){//books
                cout <<"Enter the book name: "<<endl;
                cin.ignore();
                getline (cin, bookName);
                cout <<"Enter the genre: " <<endl;
                cin.ignore();
                getline(cin,genre);
                Book* productBook = new Book (productID, productName, price, quantity, bookName, genre);
                productManager.addProduct(productBook);
                productBook->displayProduct();
                }
                
                break;
            } 

            case 2: {productManager.saveProductsToFile(); // Save products to file
            break;}

            case 3: {productManager.loadProductsFromFile(); // Load products from file
            break;} 
 
            case 4: { // Add and display customer
                int customerID;
                string customerName, contactPhone;
                cout << "Enter Customer ID: " <<endl; // Input customer details from the user
                cin >>customerID;
                cout <<"Enter Customer Name: "<<endl;
                cin.ignore();
                getline (cin, customerName);
                cout <<"Enter the Customer Phone: " <<endl;
                getline (cin, contactPhone);

                Customer* customer = new Customer (customerID, customerName, contactPhone);
                customerManager.addCustomer(customer);

                customer->displayCustomer();
            break;
                }

            case 5: { customerManager.saveCustomersToFile(); // Save customers to file
            break;}

            case 6: { customerManager.loadCustomersFromFile();   // Load customers from file
            break;}

            case 7: { // Create and display invoice
                int invoiceID;
                int productCount;
                int purchasedQuantity;

                // Input invoice details from the user
                cout <<"Enter Invoice ID for the Invoice: " <<endl;
                cin >>invoiceID;

                cout <<"Enter number of products in the invoice: "<<endl;
                cin >> productCount;  

                if (productCount> MAX_PRODUCTS) {
                    cout <<" Product exceed limit! " <<endl;
                    break;
                }

                cout <<"Enter the purchased Quantity:" <<endl;
                cin>> purchasedQuantity;

                if (purchasedQuantity <= 0) {
                    cout << "Error: Purchased quantity must be greater than 0!" << endl;
                    break;
                           }
                // Loop to add products to invoice

                Invoice* invoice = new Invoice(invoiceID);

                for( int i = 0; i<productCount; i++){
                    int productID,quantity;
                    cout <<"Enter the productID: "<<endl;
                    cin>>productID;

                    Product* selectedProduct = productManager.productSearch(productID);

                    if(selectedProduct){
                        cout <<"Enter the quantity for product ID: " <<productID <<endl;
                        cin >>quantity;

                        if(quantity <=0){
                            cout <<"Error : Quantity must be greater than 0! "<<endl;
                            continue;
                        }

                        if(quantity > selectedProduct->getproductQuantity()){
                            cout <<"Error :Quantity exceeds available stock. Available: "<<selectedProduct->getproductQuantity() <<endl;
                            continue;
                        }
                        // Call decreaseQuantity method to update stock
                         bool stockUpdated = selectedProduct->decreaseQuantity(quantity);
                         if (stockUpdated) { 
                            // Display the updated quantity after stock is decreased
                cout << "Updated stock for product " << selectedProduct->getproductName() 
                     << " is: " << selectedProduct->getproductQuantity() << endl;       
                           invoice->addProduct(selectedProduct,quantity);
                          } else {
                        cout <<"Failed to update stock for product ID: " << productID <<endl;
                          continue;
                         }
                         } else {
                          cout <<"Product not found!" <<endl;
                            }   }
                invoice->caltotalAmount(); // Calculate total amount
                invoice->displayInvoice(); // Display invoice details

                invoiceManager.addInvoice(invoice); // Add invoice to manager
              
                
                break;
                }

            case 8:{invoiceManager.saveInvoicesToFile();  // Save invoice to file
                break;
            }
            
            case 9: { // Search for product by ID
                int searchID;
                cout <<"Enter the product ID to search: ";
                cin >> searchID;
                Product* product = productManager.productSearch(searchID);
                if (product){
                    product->displayProduct();
                }else {
                    cout <<"Product not found!" <<endl;
                }
                break;} 

            case 10: {// Search for customer by ID
                int searchID;
                cout << "Enter customer ID to search: " <<endl;
                cin >> searchID;
                Customer* customer = customerManager.customerSearch(searchID);

                if (customer) {
                customer->displayCustomer();  // Show customer details if found
                } else {
                 cout << "Customer not found!" << endl;
                }
                break;} 

            case 11: {// Search for invoice by ID
                int searchID;
                cout <<"Enter the Invoice ID to search: "<<endl;
                cin >>searchID;
                Invoice* invoice = invoiceManager.invoiceSearch(searchID);
                 if(invoice) {
                    invoice->displayInvoice();
                 }else {
                    cout <<"Invoice not found!" <<endl;
                 }
                break;} 

            case 12: {  // Exit the program
                cout <<"Exiting......" <<endl;
                break; } 
                default: { // Invalid input handling
                cout <<"Invalid choice! Try again."<<endl;
                } 
        }
    } while ( option != 12); // Continue until user chooses to exit

    return 0; // End of the program
}

