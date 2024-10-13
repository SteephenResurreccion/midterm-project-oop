#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>

using namespace std;

bool validDouble(string input, double &amount) {
	if (input.length() > 7){
		cout << "	Invalid input: Float exceeds 7 characters." << endl;
		return false;
	}
	if (input == "0"){
		cout<< "	Invalid Input: Price cannot be 0."<< endl;
		return false;
	}
	bool decimalPoint = false;
	int decimalCount = 0;
	for (char c : input) {
		if (!isdigit(c)) {
			if (c == '.' && !decimalPoint) {
				decimalPoint = true;
			} else {
				cout << "	Invalid input" << endl;
				return false;
			}
		} else if (decimalPoint) {
			decimalCount++;
		}
	}
	if (decimalCount > 2) {
		cout << "	Invalid input: Float can only have 2 digits after the decimal point." << endl;
		return false;
	}
	try {
		amount = stod(input);
		return true;
	} catch (...) {
		cout << "	Invalid input" << endl;
		return false;
	}
}

bool validInteger(string input, int &amount) {
    if (input.length() > 6) {
        cout << "	Invalid input: Integer exceeds 6 digits." << endl;
        return false;
    }
    for (char c : input) {
        if (!isdigit(c)) {
            cout << "	Invalid input" << endl;
            return false;
        }
    }
    try {
        amount = stoi(input);
        return true;
    } catch (...) {
        cout << "	Invalid input" << endl;
        return false;
    }
}

bool hasDecimal(const string& priceInput) {
    return priceInput.find('.') != string::npos;
}

class ItemClass {
private:
	string id, name, category;
	int quantity;
	double price;
public:
	
	ItemClass(string productId, string productName, string productCategory, int productQuantity, double productPrice) : id(productId), name(productName), category(productCategory), quantity(productQuantity), price(productPrice) {}

	virtual void displayItem() const {
			cout << setw(10) << id.substr(0, 6) << setw(35) << name.substr(0, 30)	<< setw(10) << quantity	<< setw(12) << price; 	cout << endl;
	}
	string getName() const {
		return name;
	}
	string getCategory() const {
		return category;
	}
	double getPrice() const {
		return price;
	}
	string getId() const {
		return id;
	}
	int getQuantity() const {
		return quantity;
	}
	void updateItem(int newQuantity, double newPrice) {
		quantity = newQuantity;
		price = newPrice;
	}
};

class ItemClothing : public ItemClass {
public:
    ItemClothing(string productId, string productName, int productQuantity, float productPrice) : ItemClass(productId, productName, "Clothing", productQuantity, productPrice) {}
    void displayItem() const override {
        cout << left << setw(15) << getCategory().substr(0, 15); 
        ItemClass::displayItem();
    }
};

class ItemElectronics : public ItemClass {
public:
    ItemElectronics(string productId, string productName, int productQuantity, float productPrice) : ItemClass(productId, productName, "Electronics", productQuantity, productPrice) {}
    void displayItem() const override {
        cout << left << setw(15) << getCategory().substr(0, 15);
        ItemClass::displayItem();
    }
};

class ItemEntertainment : public ItemClass {
public:
    ItemEntertainment(string productId, string productName, int productQuantity, float productPrice) : ItemClass(productId, productName, "Entertainment", productQuantity, productPrice) {}
    void displayItem() const override {
        cout << left << setw(15) << getCategory().substr(0, 15);
        ItemClass::displayItem();
    }
};

class ItemStore {
private:
	ItemClass** products;
	int capacity, productCount, clothingCount, electronicsCount, entertainmentCount;
public:
	ItemStore() {
		capacity = 10; productCount = 0; clothingCount = 0; electronicsCount = 0; entertainmentCount = 0;
		products = new ItemClass*[capacity];
	}
	
	~ItemStore() {
		for (int i = 0; i < productCount; i++) {
			delete products[i];
		}
		delete[] products;
	}
	
	void addItem(string productId, string category, string productName, int quantity, float price) {
        if (productCount >= capacity) {
            resize();
        }
        if (category == "clothing") {
            products[productCount++] = new ItemClothing(productId, productName, quantity, price);
        } else if (category == "electronics") {
            products[productCount++] = new ItemElectronics(productId, productName, quantity, price);
        } else if (category == "entertainment") {
            products[productCount++] = new ItemEntertainment(productId, productName, quantity, price);
        } else {
            cout << "\tInvalid category." << endl;
        }
    }
    
    int getItemQuantity(const std::string& id) const {
		for (int i = 0; i < productCount; i++) {
			if (products[i]->getId() == id) {
				return products[i]->getQuantity();
			}
		}
		return -1;
	}
	
	double getItemPrice(const std::string& id) const {
		for (int i = 0; i < productCount; i++) {
			if (products[i]->getId() == id) {
				return products[i]->getPrice();
			}
		}
		return -1.0;
	}

	void resize() {
		capacity *= 2;
		ItemClass** newProducts = new ItemClass*[capacity];
		for (int i = 0; i < productCount; i++) {
			newProducts[i] = products[i];
		}
		delete[] products;
		products = newProducts;
	}

	void displayItemsByCategory(const string& category) const {
		cout << "Items in Category: " << category << endl;
		string lowerCategory = toLowercase(category);
		bool foundItems = false; 
		cout << left << setw(15) << "Category" << setw(10) << "ID" << setw(35) << "Product Name" << setw(10) << "Quantity" << setw(12) << "Price" << endl;
		cout << string(82, '-') << endl;
		for (int i = 0; i < productCount; i++) {
			string tempCategory = toLowercase(products[i]->getCategory());
			if (tempCategory == lowerCategory) {
				products[i]->displayItem();
				foundItems = true; 
			}
		}
		if (!foundItems) {
			cout << "	No items found in this category." << endl; 
		}
	}
	
	void displayAllItems() const {
		if (productCount == 0) {
			cout << "	No items available in the store." << endl; 
			return;
		}
		cout << left << setw(15) << "Category" << setw(10) << "ID" << setw(35) << "Product Name" << setw(10) << "Quantity" << setw(12) << "Price" << endl;
		cout << string(82, '-') << endl;
		for (int i = 0; i < productCount; i++) {
			cout << left << setw(15) << products[i]->getCategory().substr(0, 15) << setw(10) << products[i]->getId().substr(0, 6) << setw(35) << products[i]->getName().substr(0, 30) << setw(10) << products[i]->getQuantity() << setw(12) << fixed << setprecision(2) << products[i]->getPrice()<<endl; 
		}
	}
	
	void sortItemsByQuantity(bool ascending) {
		ItemClass** sortedProducts = new ItemClass*[productCount];
		for (int i = 0; i < productCount; i++) {
			sortedProducts[i] = products[i];
		}
		for (int i = 0; i < productCount - 1; i++) {
			for (int j = 0; j < productCount - i - 1; j++) {
				if ((ascending && sortedProducts[j]->getQuantity() > sortedProducts[j + 1]->getQuantity()) ||
					(!ascending && sortedProducts[j]->getQuantity() < sortedProducts[j + 1]->getQuantity())) {
					ItemClass* temp = sortedProducts[j];
					sortedProducts[j] = sortedProducts[j + 1];
					sortedProducts[j + 1] = temp;
				}
			}
		}
		cout << "Sorted Items by Quantity (" << (ascending ? "Ascending" : "Descending") << "):" << endl;
		cout << left << setw(15) << "Category" << setw(10) << "ID" << setw(35) << "Product Name" << setw(10) << "Quantity" << setw(12) << "Price" << endl;
		cout << string(82, '-') << endl;
		for (int i = 0; i < productCount; i++) {
			cout << left << setw(15) << sortedProducts[i]->getCategory().substr(0, 15) << setw(10) << sortedProducts[i]->getId().substr(0, 6) << setw(35) << sortedProducts[i]->getName().substr(0, 30) << setw(10) << sortedProducts[i]->getQuantity() << setw(12) << fixed << setprecision(2) << sortedProducts[i]->getPrice() << endl;
		}
		delete[] sortedProducts;
	}
	
	void sortItemsByPrice(bool ascending) {
		ItemClass** sortedProducts = new ItemClass*[productCount];
		for (int i = 0; i < productCount; i++) {
			sortedProducts[i] = products[i];
		}
		for (int i = 0; i < productCount - 1; i++) {
			for (int j = 0; j < productCount - i - 1; j++) {
				if ((ascending && sortedProducts[j]->getPrice() > sortedProducts[j + 1]->getPrice()) ||
					(!ascending && sortedProducts[j]->getPrice() < sortedProducts[j + 1]->getPrice())) {
					ItemClass* temp = sortedProducts[j];
					sortedProducts[j] = sortedProducts[j + 1];
					sortedProducts[j + 1] = temp;
				}
			}
		}
		cout << "Sorted Items by Price (" << (ascending ? "Ascending" : "Descending") << "):" << endl;
		cout << left << setw(15) << "Category" << setw(10) << "ID" << setw(35) << "Product Name" << setw(10) << "Quantity" << setw(12) << "Price" << endl;
		cout << string(82, '-') << endl;
		for (int i = 0; i < productCount; i++) {
			cout << left << setw(15) << sortedProducts[i]->getCategory().substr(0, 15) << setw(10) << sortedProducts[i]->getId().substr(0, 6) << setw(35) << sortedProducts[i]->getName().substr(0, 30) << setw(10) << sortedProducts[i]->getQuantity() << setw(12) << fixed << setprecision(2) << sortedProducts[i]->getPrice() << endl;
		}
		delete[] sortedProducts;
	}

	void updateItem(string id, int newQuantity, float newPrice) {
		string lowerId = toLowercase(id);
		for (int i = 0; i < productCount; i++) {
			if (toLowercase(products[i]->getId()) == lowerId) {
				products[i]->updateItem(newQuantity, newPrice);
				cout << "	Item updated successfully." << endl;
				return;
			}
		}
		cout << "	Item not found." << endl;
	}

	void removeItem(string id) {
		string lowerId = toLowercase(id);
		for (int i = 0; i < productCount; i++) {
			if (toLowercase(products[i]->getId()) == lowerId) {
				delete products[i];
				for (int j = i; j < productCount - 1; j++) {
					products[j] = products[j + 1];
				}
				productCount--;
				cout << "	Item removed successfully." << endl;
				return;
			}
		}
		cout << "	Item not found." << endl;
	}

	bool isItemValid(const string &searchID) const {
		if (searchID.empty()) {
	        cout << "Error: Item ID cannot be empty." << endl;
	        return false;
	    }
		string tempSearchID = toLowercase(searchID); 
		for (int i = 0; i < productCount; i++) {
			string tempID = toLowercase(products[i]->getId()); 
			if (tempID == tempSearchID) {
				return true;
			}
		}
		return false;
	}
	
	bool isItemValidNonCS(const string &searchID) const {
		if (searchID.empty()) {
	        cout << "Error: Item ID cannot be empty." << endl;
	        return false;
	    }
		for (int i = 0; i < productCount; i++) {
			if (searchID == products[i]->getId()) {
				return true;
			}
		}
		return false;
	}

	string toLowercase(const string &input) const {
		string result = input;
		for (char &c : result) {
			c = tolower(c);
		}
		return result;
	}

	bool validateCategory(const string &category, string &output) const {
		string lowerCategory = toLowercase(category);
		output = lowerCategory;
		return (lowerCategory == "clothing" || lowerCategory == "electronics" || lowerCategory == "entertainment");
	}

	void displaySearchedItemByID(string searchID) const {
		string tempSearchID = toLowercase(searchID);
		bool found = false;
		cout << left << setw(15) << "Category" << setw(10) << "ID" << setw(35) << "Product Name" << setw(10) << "Quantity" << setw(12) << "Price" << endl;
		cout << string(82, '-') << endl;
		for (int i = 0; i < productCount; i++) {
			string tempID = toLowercase(products[i]->getId());
			if (tempID == tempSearchID) {
				products[i]->displayItem();
				found = true;
			}
		}
	}

	void displayLowStockItems() const {
		bool foundLowStock = false;
		for (int i = 0; i < productCount; i++) {
			if (products[i]->getQuantity() <= 5) {
				if (!foundLowStock) {
					cout << "Low Stock Items (Quantity <= 5):" << endl;
					cout << left << setw(15) << "Category" << setw(10) << "ID" << setw(35) << "Product Name" << setw(10) << "Quantity" << setw(12) << "Price" << endl;
					cout << string(82, '-') << endl;
					foundLowStock = true;
				}
				products[i]->displayItem();
			}
		}
		if (!foundLowStock) {
			cout << "	No low stock items available." << endl;
		}
	}
	
	bool hasProducts() const {
	    return productCount > 0;
	}
};

int main() {
	ItemStore store;
	string name, category, searchID, id, quantityInput, priceInput, choiceInput, sortOrder, sortOption, lowerOutput;
	int quantity, currentQuantity, choice;
	double price, currentPrice;
	bool valid = true;

	while (valid == true) {
		cout << "\n --Main Menu--\n\n1. Add Item\n2. Update Item\n3. Remove Item\n4. Display Items by Category\n5. Display All Items\n6. Search product\n7. Sort Items\n8. Display Low Stock Items\n9. Exit\n";
		cout << "Choose an option: ";
		getline(cin, choiceInput);
		while (!validInteger(choiceInput, choice) || (choice < 1 || choice > 9)) {
			cout << "Must be a number from 1-9: ";
			getline(cin, choiceInput);
		}
		switch (choice) {
			case 1:
				cout << "Enter product category (Clothing, Electronics, Entertainment): ";
				getline(cin, category);
				while (!store.validateCategory(category, lowerOutput)) {
					cout << "Invalid category. Please enter Clothing, Electronics, or Entertainment: ";
					getline(cin, category);
				}
				cout << "Enter product ID (max 6 characters): ";
				getline(cin, id);
				while (id.empty()) {
					cout << "Cannot be blank, Try again: ";
					getline(cin, id);
				}
				while (id.length() > 6) {
					cout << "ID exceeds character limit of 6, try again: ";
					getline(cin, id);
				}
				while (store.isItemValidNonCS(id)) {
					cout << "Item ID already exists. Please enter a unique ID: ";
					getline(cin, id);
				}
				cout << "Enter product name (max 30 characters): ";
				getline(cin, name);
				while (name.empty()) {
					cout << "Cannot be blank, Try again: ";
					getline(cin, name);
				}
				while (name.length() > 30) {
					cout << "Product name exceeds character limit of 30.";
					getline(cin, name);
				}
				cout << "Enter product quantity (maximum of 6 digits): ";
				getline(cin, quantityInput);
				while (!validInteger(quantityInput, quantity)) {
					cout << "Enter product quantity (maximum of 6 digits): ";
					getline(cin, quantityInput);
				}
				cout << "Enter product price (maximum of 7 digits): ";
				getline(cin, priceInput);
				while (!validDouble(priceInput, price)) {
					cout << "Enter product price (maximum of 7 digits): ";
					getline(cin, priceInput);
				}
				store.addItem(id, lowerOutput, name, quantity, price);
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			case 2: 
				if (!store.hasProducts()) {
    				cout << "There are no products in the store." << endl;
    				cout<< "Press Any Key To Continue";getch(); system("cls");break;
    			}
				cout << "Enter item ID to update, Input 0 to go back: ";
				getline(cin, id);
				if(id=="0"){
					cout<<"Press Any Key To Continue";getch(); system("cls");break;
				}
				while (!store.isItemValidNonCS(id)) {
					cout << "Invalid item ID. Please try again, input 0 to go back: ";
					getline(cin, id);
					if(id=="0"){
						cout<<"Press Any Key To Continue";getch(); system("cls");break;
					}
				}
				if(id=="0"){
					break;
				}
				currentQuantity = store.getItemQuantity(id);
				currentPrice = store.getItemPrice(id);
				cout << "Current Quantity: " << currentQuantity << endl;
				cout << "Current Price: " << fixed << setprecision(2) << currentPrice << endl;
				cout << "Do you want to update by: \n(1) Quantity \n(2) Price\nInput here: ";
				getline(cin, choiceInput);
				while (!validInteger(choiceInput, choice) || (choice != 1 && choice != 2)) {
					cout << "	Invalid option. Please enter \n(0) to go back \n(1) for Quantity \n(2) for Price: ";
					getline(cin, choiceInput);
					if(choiceInput=="0"){
						cout<<"Press Any Key To Continue";getch(); system("cls");break;
					}
				}
				if(choiceInput=="0"){
					break;
				}
				if (choice == 1) {
					cout << "Enter new quantity: ";
					getline(cin, quantityInput);
					while (to_string(currentQuantity) == quantityInput){
						cout << "Must not be the same as current quantity: ";
						getline(cin, quantityInput);
					}
					while (!validInteger(quantityInput, quantity)) {
						cout << "Invalid Integer. Only enter numbers for quantity: ";
						getline(cin, quantityInput);
					}
					store.updateItem(id, quantity, currentPrice);
				} else if (choice == 2) {
					cout << "Enter new price: ";
					getline(cin, priceInput);
					while (!validDouble(priceInput, price)) {
						cout << "Invalid Double. Only enter numbers for price: ";
						getline(cin, priceInput);
					}
					while (price == currentPrice) {
				        cout << "Must not be the same as current price: ";
				        getline(cin, priceInput);
					    while (!validDouble(priceInput, price)) {
							cout << "Invalid Double. Only enter numbers for price: ";
							getline(cin, priceInput);
						}
					}
					cout << "Previous price: " << fixed << setprecision(2) << currentPrice << " updated to " << fixed << setprecision(2) << price << endl;
					store.updateItem(id, currentQuantity, price);
				}
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			case 3:
				if (!store.hasProducts()) {
    				cout << "There are no products in the store." << endl;
    				cout<< "Press Any Key To Continue";getch(); system("cls");break;
    			}
				cout << "Enter item ID to remove, Input 0 to go back: ";
				getline(cin, id);
				if(id=="0"){
					cout<<"Press Any Key To Continue";getch(); system("cls");break;
				}
				while (!store.isItemValidNonCS(id)) {
					cout << "	Invalid item ID. Please try again: " << endl;
					getline(cin, id);
				}
				store.removeItem(id);
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			case 4:
				if (!store.hasProducts()) {
    				cout << "There are no products in the store." << endl;
    				cout<< "Press Any Key To Continue";getch(); system("cls");break;
    			}
				cout << "Enter category (Clothing, Electronics, Entertainment): ";
				getline(cin, category);
				while (!store.validateCategory(category, lowerOutput)) {
					cout << "	Invalid category. Please enter Clothing, Electronics, or Entertainment: ";
						getline(cin, category);
				}
				store.displayItemsByCategory(lowerOutput);
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			case 5:
				cout<< "Display All Items: \n"<<endl;
				store.displayAllItems();
				cout<<"\nSuccessful. Press Any Key To Continue";getch(); system("cls");break;
			case 6:
				if (!store.hasProducts()) {
    				cout << "There are no products in the store." << endl;
    				cout<< "Press Any Key To Continue";getch(); system("cls");break;
    			}
				cout << "Enter item ID to search, Input 0 to go back: ";
				getline(cin, searchID);
				if(searchID=="0"){
					cout<<"Press Any Key To Continue";getch(); system("cls");break;
				}
				while (!store.isItemValid(searchID)) {
					cout << "	Item not found, Please try again: ";
					getline(cin, searchID);
				}
				store.displaySearchedItemByID(searchID);
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			case 7:
				if (!store.hasProducts()) {
    				cout << "There are no products in the store." << endl;
    				cout<< "Press Any Key To Continue";getch(); system("cls");break;
    			}
				cout << "Sort by (P for Price, Q for Quantity): ";
				getline(cin, sortOption);
				while(!(sortOption == "P"||sortOption == "p"||sortOption == "Q"||sortOption == "q")){
					cout << "P for Price, and Q for Quantity only: ";
					getline(cin, sortOption);
				}
				if (sortOption == "P" || sortOption == "p") {
					cout << "Sort by price (A for ascending, D for descending): ";
					getline(cin, sortOrder);
					while(!(sortOrder =="A"||sortOrder =="a"||sortOrder =="D"||sortOrder =="d")){
						cout << "A for ascending, D for descending: ";
						getline(cin, sortOrder);
					}
					if (sortOrder == "A" || sortOrder == "a")
						store.sortItemsByPrice(true);
					else if (sortOrder == "D" || sortOrder == "d")
						store.sortItemsByPrice(false);
				} else if (sortOption == "Q" || sortOption == "q") {
					cout << "Sort by quantity (A for ascending, D for descending): ";
					getline(cin, sortOrder);
					while(!(sortOrder=="A"||sortOrder=="a"||sortOrder=="D"||sortOrder=="d")){
						cout << "A for ascending, D for descending: ";
						getline(cin, sortOrder);
					}
					if (sortOrder == "A" || sortOrder == "a")
						store.sortItemsByQuantity(true);
						else if (sortOrder == "D" || sortOrder == "d")
						store.sortItemsByQuantity(false);
				}
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			case 8:
				if (!store.hasProducts()) {
    				cout << "There are no products in the store." << endl;
    				cout<< "Press Any Key To Continue";getch(); system("cls");break;
    			}
				store.displayLowStockItems();
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			case 9:
				cout << "	Exiting the program." << endl;
				valid = false;
				cout<<"Successful. Press Any Key To Continue";getch(); system("cls");break;
			default:
				cout << "	Invalid option. Please choose again." << endl;
				cout<<"Press Any Key To Continue";getch(); system("cls");break;
		}
	}
	return 0;
}