#pragma warning(disable : 4996)
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

struct CustomerObj
{
	int prog_id;
	int ID;
	char Name[40];
	int PhoneNo;
	int Age;
	int EmergencyNo;
	char Email[50];
	char Address[60];
	char Gender[6];
};
struct DamagedObj {
	int coordinate[2];
};
struct RentedObj {
	bool rented;
	CustomerObj customer;
};
struct VehicleObj {
	int prog_id;
	char classification[10];
	char trim[10];
	bool automatic;
	DamagedObj damage[30];
	int damagetotal;
	int milage;
	int quantity;
	RentedObj rented;
	char licenceplate[20];
	char modelnumber[17];
	char make[20];
	int modelyear;
	char modelname[20];
	float price;
};
struct DiscountObj {
	VehicleObj vehicle;
	float discountpercentage;
};

void menu(int cs, char c[][150], int size, char title[50], bool dospace);
void Menu(int cs, char c[][150], int size, char title[50]) { menu(cs, c, size, title, true); }
void selection(int *cs, char c[][150], int size, int y, int x, char title[50], bool dospace);
void Selection(int* cs, char c[][150], int size, char title[50]) { selection(cs, c, size, 0, 0, title, true); }
void clear(int y, int x);
void Customer();
void Vehicle();
void MainMenu();
void back(char m);
void Credits();
void ManageCustomer();
void ManageVehicles();
void RecieveVehicle();
void RentVehicle();
CustomerObj SearchCustomer(bool select);
CustomerObj searchcustomer() { return SearchCustomer(false); }
CustomerObj CreateCustomer();
char* Question(char question[], char type);
int Question(char question[]);
float Questionf(char question[]);
void init();
void printTitle();
DamagedObj CarDamage(int* vs, int* hs, int id);
VehicleObj SearchVehicle(bool select);
VehicleObj searchvehicle() { return SearchVehicle(false); }
void ManageDiscount();
bool Pay(float price);

CONSOLE_SCREEN_BUFFER_INFO coninfo;
HANDLE hConsole;
FILE* CustomersDB;
FILE* VehiclesDB;
FILE* BlacklistDB;
FILE* DiscountDB;
int maxcid = 0;
int maxvid = 0;

int main(void)
{
	system("MODE 120, 40");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("title The Car Rental App");
	SetConsoleTextAttribute(hConsole, 6);
	int strglen = strlen("\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\ ");
	int spacing = (coninfo.dwSize.X + strglen) / 2;
	printf("%*s __      __       .__                               \n", spacing, "");
	printf("%*s/  \\    /  \\ ____ |  |   ____  ____   _____   ____  \n", spacing, "");
	printf("%*s\\   \\/\\/   // __ \\|  | _/ ___\\/  _ \\ /     \\_/ __ \\ \n", spacing, "");
	printf("%*s \\        /\\  ___/|  |_\\  \\__(  <_> )  Y Y  \\  ___/ \n", spacing, "");
	printf("%*s  \\__/\\  /  \\___  >____/\\___  >____/|__|_|  /\\___  >\n", spacing, "");
	printf("%*s       \\/       \\/          \\/            \\/     \\/ \n", spacing, "");
	strglen = strlen("  |  | /  _ \\    |  |   |  |  \\_/ __ \\ ");
	spacing = (coninfo.dwSize.X + strglen) / 2;
	printf("%*s_________      _________.__            \n", spacing, "");
	printf("%*s\\__  ___/___   \\__  ___/|  |__   ____  \n", spacing, "");
	printf("%*s  |  | /  _ \\    |  |   |  |  \\_/ __ \\ \n", spacing, "");
	printf("%*s  |  |(  <_> )   |  |   |   Y  \\  ___/ \n", spacing, "");
	printf("%*s  |__| \\____/    |__|   |___|  /\\___  > \n", spacing, "");
	printf("%*s                             \\/     \\/ \n", spacing, "");
	printf("%15s_________                __________               __         .__       _____                 \n", "");
	printf("%15s\\_   ___ \\_____ _______  \\______   \\ ____   _____/  |______  |  |     /  _  \\ ______ ______  \n", "");
	printf("%15s/    \\  \\/\\__  \\\\_  __ \\  |       _// __ \\ /    \\   __\\__  \\ |  |    /  /_\\  \\\\____ \\\\____ \\ \n", "");
	printf("%15s\\     \\____/ __ \\|  | \\/  |    |   \\  ___/|   |  \\  |  / __ \\|  |__ /    |    \\  |_> >  |_> >\n", "");
	printf("%15s \\______  (____  /__|     |____|_  /\\___  >___|  /__| (____  /____/ \\____|__  /   __/|   __/ \n", "");
	printf("%15s        \\/     \\/                \\/     \\/     \\/          \\/               \\/|__|   |__|    \n\n\n\n", "");
	SetConsoleTextAttribute(hConsole, 15);
	printf("Please Wait ....");
	init();
	Sleep(1500);
	system("cls");
	MainMenu();
}

void clear(int y, int x) {
	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y = 0;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
}

void menu(int cs, char c[][150], int size, char title[50], bool dospace)  {
	SetConsoleTextAttribute(hConsole, 6);
	printTitle();
	if (sizeof(title) > 1) {
		int ret;
		ret = GetConsoleScreenBufferInfo(hConsole, &coninfo);
		if (ret)
		{
			int stringlength = strlen(title);
			int spacing = (coninfo.dwSize.X + stringlength) / 2;
			printf("%*s\n\n\n", spacing, title);
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
	for (int i = 0; i < size; i++) {
		if (cs == i) {
			SetConsoleTextAttribute(hConsole, 3);
		}
		else {
			SetConsoleTextAttribute(hConsole, 15);
		}
		int ret;
		ret = GetConsoleScreenBufferInfo(hConsole, &coninfo);
		if (ret && dospace)
		{
			int stringlength = strlen(c[i]);
			int spacing = (coninfo.dwSize.X + stringlength) / 2 ;
			printf("%*s\n\n\n", spacing , c[i]);
		}
		else {
			printf("%s\n\n\n", c[i]);
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void selection(int *cs, char c[][150], int size, int y, int x, char title[50], bool dospace) {
	while (true) {
		if (_kbhit()) {
			int i = _getch();
			if (i == 224) {
				i = _getch();
				if (i == 72) {
					clear(y,x);
					if ((*cs) - 1 >= 0) {
						(*cs)--;
					}
					else {
						(*cs) = size-1;
					}
					menu(*cs, c, size, title, dospace);
				}
				if (i == 80) {
					clear(y, x);
					if ((*cs) + 1 < size) {
						(*cs)++;
					}
					else {
						(*cs) = 0;
					}
					menu(*cs, c, size, title, dospace);
				}
			}
			if (i == 13) {
				return;
			}
		}
	}
}

void MainMenu() {
	system("cls");
	char c[4][150] = { "Vehicle", "Customer", "Credits", "Exit" };
	int cs = 0;
	char st[30] = "";
	Menu(cs, c, 4, st);
	Selection(&cs, c, 4, st);
	switch(cs) {
		case 0:
			Vehicle();
			break;
		case 1:
			Customer();
			break;
		case 2:
			Credits();
			break;
		case 3:
			exit(0);
			break;
	}
}

void back(char m) {
	switch (m) {
		case 'm':
			MainMenu();
			break;
		case 'v':
			Vehicle();
			break;
		case 'c':
			Customer();
			break;
	}
}

void Credits() {
	system("cls");
	char c[3][30] = { "Saud Fawaz Alshareef", "Mshari Ali Dajam", "Omar Baflh" };
	SetConsoleTextAttribute(hConsole, 2);
	printf("%20s__________                                                                        \n", "");
	printf("%20s\\______   \\_______  ____   ________________    _____   _____   ___________  ______\n", "");
	printf("%20s |     ___/\\_  __ \\/  _ \\ / ___\\_  __ \\__  \\  /     \\ /     \\_/ __ \\_  __ \\/  ___/\n", "");
	printf("%20s |    |     |  | \\(  <_> ) /_/  >  | \\// __ \\|  Y Y  \\  Y Y  \\  ___/|  | \\/\\___ \\ \n", "");
	printf("%20s |____|     |__|   \\____/\\___  /|__|  (____  /__|_|  /__|_|  /\\___  >__|  /____  >\n", "");
	printf("%20s                        /_____/            \\/      \\/      \\/     \\/           \\/ \n\n\n\n", "");
	SetConsoleTextAttribute(hConsole, 15);
	for (int i = 0; i < 3; i++) {
		int stringlength = strlen(c[i]);
		int spacing = (coninfo.dwSize.X + stringlength) / 2;
		printf("%*s\n\n\n", spacing, c[i]);
	}
	Sleep(3000);
	system("cls");
	SetConsoleTextAttribute(hConsole, 3);
	printf("%25s  _________                               .__                  .___\n", "");
	printf("%25s /   _____/__ ________   ______________  _|__| ______ ____   __| _/\n", "");
	printf("%25s \\_____  \\|  |  \\____ \\_/ __ \\_  __ \\  \\/ /  |/  ___// __ \\ / __ | \n", "");
	printf("%25s /        \\  |  /  |_> >  ___/|  | \\/\\   /|  |\\___ \\\\  ___// /_/ | \n", "");
	printf("%25s/_______  /____/|   __/ \\___  >__|    \\_/ |__/____  >\\___  >____ | \n", "");
	printf("%25s        \\/      |__|        \\/                    \\/     \\/     \\/ \n\n\n\n", "");
	SetConsoleTextAttribute(hConsole, 15);
	int stringlength = strlen("Dr. Muhammad Usman Ilyas");
	int spacing = (coninfo.dwSize.X + stringlength) / 2;
	printf("%*s\n\n\n", spacing, "Dr. Muhammad Usman Ilyas");
	Sleep(3000);
	MainMenu();
}

char* Question(char question[], char type) {
	char temp[30];
	switch (type) {
		case 'q':
			SetConsoleTextAttribute(hConsole, 2);
			printf("? ");
			SetConsoleTextAttribute(hConsole, 15);
			printf("Input %s?: ", question);
			scanf_s("%s", &temp, sizeof(temp));
			GetConsoleScreenBufferInfo(hConsole, &coninfo);
			coninfo.dwCursorPosition.Y -= 1;
			coninfo.dwCursorPosition.X = 0;
			SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
			SetConsoleTextAttribute(hConsole, 2);
			printf("? ");
			SetConsoleTextAttribute(hConsole, 15);
			printf("%s: ", question);
			SetConsoleTextAttribute(hConsole, 3);
			printf("%-50s\n", temp);
			SetConsoleTextAttribute(hConsole, 15);
			break;
		case 'y':
			SetConsoleTextAttribute(hConsole, 2);
			printf("? ");
			SetConsoleTextAttribute(hConsole, 15);
			printf("%s?(y/n): ", question);
			scanf_s("%s", &temp, sizeof(temp));
			while (strcmp(temp, "y") != 0 && strcmp(temp, "n") != 0) {
				SetConsoleTextAttribute(hConsole, 2);
				printf("? ");
				SetConsoleTextAttribute(hConsole, 15);
				printf("%s?(y/n): ", question);
				scanf_s("%s", &temp, sizeof(temp));
			}
			if (strcmp(temp, "y") == 0) {
				strcpy(temp, "Yes");
			}
			else {
				strcpy(temp, "No");
			}
			GetConsoleScreenBufferInfo(hConsole, &coninfo);
			coninfo.dwCursorPosition.Y -= 1;
			coninfo.dwCursorPosition.X = 0;
			SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
			SetConsoleTextAttribute(hConsole, 2);
			printf("? ");
			SetConsoleTextAttribute(hConsole, 15);
			printf("%s: ", question);
			SetConsoleTextAttribute(hConsole, 3);
			printf("%-50s\n", temp);
			SetConsoleTextAttribute(hConsole, 15);
			break;
		case 'm':
			SetConsoleTextAttribute(hConsole, 2);
			printf("? ");
			SetConsoleTextAttribute(hConsole, 15);
			printf("%s?(m/f): ", question);
			scanf_s("%s", &temp, sizeof(temp));
			while (strcmp(temp, "m") != 0 && strcmp(temp, "f") != 0) {
				SetConsoleTextAttribute(hConsole, 2);
				printf("? ");
				SetConsoleTextAttribute(hConsole, 15);
				printf("%s?(m/f): ", question);
				scanf_s("%s", &temp, sizeof(temp));
			}
			if (strcmp(temp, "m") == 0) {
				strcpy(temp, "Male");
			}
			else {
				strcpy(temp, "Female");
			}
			GetConsoleScreenBufferInfo(hConsole, &coninfo);
			coninfo.dwCursorPosition.Y -= 1;
			coninfo.dwCursorPosition.X = 0;
			SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
			SetConsoleTextAttribute(hConsole, 2);
			printf("? ");
			SetConsoleTextAttribute(hConsole, 15);
			printf("%s: ", question);
			SetConsoleTextAttribute(hConsole, 3);
			printf("%-50s\n", temp);
			SetConsoleTextAttribute(hConsole, 15);
			break;
		
	}
	for (int i = 0; temp[i]; i++) {
		temp[i] = tolower(temp[i]);
	}
	return temp;
}

int Question(char question[]) {
	int temp;
	SetConsoleTextAttribute(hConsole, 2);
	printf("? ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("Input %s?: ", question);
	scanf_s("%d", &temp);
	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y -= 1;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
	SetConsoleTextAttribute(hConsole, 2);
	printf("? ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("%s: ", question);
	SetConsoleTextAttribute(hConsole, 3);
	printf("%-50d\n", temp);
	SetConsoleTextAttribute(hConsole, 15);
	return temp;
}

float Questionf(char question[]) {
	float temp;
	SetConsoleTextAttribute(hConsole, 2);
	printf("? ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("Input %s?: ", question);
	scanf_s("%f", &temp);
	GetConsoleScreenBufferInfo(hConsole, &coninfo);
	coninfo.dwCursorPosition.Y -= 1;
	coninfo.dwCursorPosition.X = 0;
	SetConsoleCursorPosition(hConsole, coninfo.dwCursorPosition);
	SetConsoleTextAttribute(hConsole, 2);
	printf("? ");
	SetConsoleTextAttribute(hConsole, 15);
	printf("%s: ", question);
	SetConsoleTextAttribute(hConsole, 3);
	printf("%-50.2f\n", temp);
	SetConsoleTextAttribute(hConsole, 15);
	return temp;
}

void init() {
	CustomersDB = fopen("CustomersDB.txt", "a");
	VehiclesDB = fopen("VehiclesDB.txt", "a");
	BlacklistDB = fopen("BlacklistDB.txt", "a");
	DiscountDB = fopen("DiscountDB.txt", "a");
	struct CustomerObj customer1;
	while (fread(&customer1, sizeof(struct CustomerObj), 1, CustomersDB)) {
		if (customer1.prog_id > maxcid) {
			maxcid = customer1.prog_id;
		}
	}
	struct VehicleObj vehicle;
	while (fread(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB)) {
		if (vehicle.prog_id > maxvid) {
			maxvid = vehicle.prog_id;
		}
	}

}

void printTitle() {
	printf("%15s_________                __________               __         .__       _____                 \n", "");
	printf("%15s\\_   ___ \\_____ _______  \\______   \\ ____   _____/  |______  |  |     /  _  \\ ______ ______  \n", "");
	printf("%15s/    \\  \\/\\__  \\\\_  __ \\  |       _// __ \\ /    \\   __\\__  \\ |  |    /  /_\\  \\\\____ \\\\____ \\ \n", "");
	printf("%15s\\     \\____/ __ \\|  | \\/  |    |   \\  ___/|   |  \\  |  / __ \\|  |__ /    |    \\  |_> >  |_> >\n", "");
	printf("%15s \\______  (____  /__|     |____|_  /\\___  >___|  /__| (____  /____/ \\____|__  /   __/|   __/ \n", "");
	printf("%15s        \\/     \\/                \\/     \\/     \\/          \\/               \\/|__|   |__|    \n\n\n\n", "");
}

void Vehicle() {
	system("cls");
	char c[5][150] = { "Manage Vehicle", "Recieve Rented Vehicle","Search Vehicle", "Rent Vehicle", "Back" };
	int cs = 0;
	char st[30] = "";
	Menu(cs, c, 5, st);
	Selection(&cs, c, 5, st);
	switch (cs) {
	case 0:
		ManageVehicles();
		printf("\n\n\n\nPress Enter To Continue...");
		while (true) {
			if (_kbhit()) {
				int i = _getch();
				if (i == 13) {
					back('v');
				}
			}
		}
		break;
	case 1:
		RecieveVehicle();
		printf("\n\n\n\nPress Enter To Continue...");
		while (true) {
			if (_kbhit()) {
				int i = _getch();
				if (i == 13) {
					back('v');
				}
			}
		}
		break;
	case 2:
		SearchVehicle(false);
		printf("\n\n\n\nPress Enter To Continue...");
		while (true) {
			if (_kbhit()) {
				int i = _getch();
				if (i == 13) {
					back('v');
				}
			}
		}
		break;
	case 3:
		RentVehicle();
		printf("\n\n\n\nPress Enter To Continue...");
		while (true) {
			if (_kbhit()) {
				int i = _getch();
				if (i == 13) {
					back('v');
				}
			}
		}
		break;
	case 4:
		back('m');
		break;
	}
}

void ManageVehicles() {
	system("cls");
	char c[5][150] = { "Add Vehicle", "Edit Vehicle", "Delete Vehicle", "Discount Vehicle" , "Back" };
	int cs = 0;
	char st[30] = "";
	Menu(cs, c, 5, st);
	Selection(&cs, c, 5, st);
	switch (cs) {
		case 0:
			{
				VehiclesDB = fopen("VehiclesDB.txt", "a");
				system("cls");
				SetConsoleTextAttribute(hConsole, 6);
				printTitle();
				SetConsoleTextAttribute(hConsole, 15);
				struct VehicleObj vehicle;
				char sel1[13][30] = { "Classification", "Trim", "Automatic", "Milage", "Quantity", "Licence Plate", "Model Number", "Make", "Model Name", "Model Year" , "How Many Damage", "Rented", "Daily Price" };
				strcpy(vehicle.classification, Question(sel1[0], 'q'));
				strcpy(vehicle.trim, Question(sel1[1], 'q'));
				if (strcmp(Question(sel1[2], 'y'), "yes") == 0) {
					vehicle.automatic = true;
				}
				else {
					vehicle.automatic = false;
				}
				vehicle.milage = Question(sel1[3]);
				vehicle.quantity = Question(sel1[4]);
				strcpy(vehicle.licenceplate, Question(sel1[5], 'q'));
				strcpy(vehicle.modelnumber, Question(sel1[6], 'q'));
				strcpy(vehicle.make, Question(sel1[7], 'q'));
				strcpy(vehicle.modelname, Question(sel1[8], 'q'));
				vehicle.modelyear = Question(sel1[9]);
				for (int i = 0; i < vehicle.quantity; i++) {
					vehicle.price = Questionf(sel1[12]);
					int damagecount = Question(sel1[10]);
					vehicle.damagetotal = 0;
					for (int i = 0; i < damagecount; i++) {
						int vs = 16, hs = 17;
						DamagedObj cd1 = CarDamage(&vs, &hs, i + 1);
						vehicle.damage[i] = cd1;
						vehicle.damagetotal++;
					}
					if (damagecount > 0) {
						SetConsoleTextAttribute(hConsole, 6);
						printTitle();
						SetConsoleTextAttribute(hConsole, 15);
					}
					if (vehicle.quantity > 1) {
						printf("Vehicle #%d\n", i + 1);
					}
					if (strcmp(Question(sel1[11], 'y'), "yes") == 0) {
						CustomerObj customerrented = SearchCustomer(true);
						if (customerrented.prog_id > 0) {
							RentedObj rented = { true, customerrented };
							vehicle.rented = rented;
							system("cls");
							SetConsoleTextAttribute(hConsole, 6);
							printTitle();
							SetConsoleTextAttribute(hConsole, 15);
						}
						else {
							RentedObj notrented = { false };
							vehicle.rented = notrented;
							printf("\n\n\n\nPress Enter To Continue...");
							while (true) {
								if (_kbhit()) {
									int i = _getch();
									if (i == 13) {
										system("cls");
										break;
									}
								}
							}
						}

					}
					else {
						RentedObj notrented = { false };
						vehicle.rented = notrented;
					}
					printf("\n\n\nClassification = %s \nTrim = %s \nAutomatic = %s\n", vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False");
					printf("HasDamage = %s \nMilage = %d \nQuatity = %d\n", (vehicle.damagetotal > 0) ? "True" : "False", vehicle.milage, vehicle.quantity);
					printf("Rented = %s \nLicence Plate = %s \nModel Number = %s\n", (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber);
					printf("Make = %s \nModel Year = %d \nModel Name = %s \nDaily Price = %f\n", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
					Sleep(500);
					if (vehicle.quantity > 1) {
						char vehicles[20];
						sprintf(vehicles, "Vehicle #%d Added", i);
						printf("\n\n\n%s\n\n\n", vehicles);
					}
					char apicall[800];
					char url[150];
					sprintf(url, "https://google-search3.p.rapidapi.com/api/v1/images/q=%s%%20%d%%20%s%%20%s", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.trim);
					printf("%s", "\n Loading...");
					sprintf(apicall, "powershell -noexit -command \"$headers=@{};$headers.Add(\\\"x-rapidapi-key\\\", \\\"35e36522ebmshcbc8fffa420ad8ap1af69fjsn744de80bfb57\\\");$headers.Add(\\\"x-rapidapi-host\\\", \\\"google-search3.p.rapidapi.com\\\");$response = Invoke-WebRequest -Uri '%s' -Method GET -Headers $headers;$src = $response.Content | ConvertFrom-Json | select -expand image_results | Select-Object -first 1 | select -expand image | select -expand src;$wc = New-Object System.Net.WebClient;$wc.DownloadFile($src, \\\".\\%s.png\\\"); exit 0\"", url, vehicle.modelnumber);
					system(apicall);
					printf("\r          ");
					printf("\r\n\n\n%s\n\n\n", "Vehicle Added");
					Sleep(500);
					maxvid++;
					vehicle.prog_id = maxvid;
					fwrite(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB);
				}
				fclose(VehiclesDB);
			}
			break;
		case 1:
			{
				system("cls");
				VehicleObj vehicle = SearchVehicle(true);
				if(vehicle.prog_id > 0){
					system("cls");
					system("MODE 150, 50");
					char c[14][150] = { "Classification", "Trim", "Automatic", "Milage", "Quantity", "Licence Plate", "Model Number", "Make", "Model Name", "Model Year" , "How Many Damage", "Rented", "Daily Price", "back" };
					int cs = 0;
					char st[30] = "What Do You Want To Edit";
					Menu(cs, c, 9, st);
					Selection(&cs, c, 9, st);
					system("MODE 120, 30");
					FILE* tempfile = fopen("temp.txt", "w");
					VehiclesDB = fopen("VehiclesDB.txt", "r");
					char x = fgetc(VehiclesDB);
					while (x != EOF)
					{
						fputc(x, tempfile);
						x = fgetc(VehiclesDB);
					}
					fclose(tempfile);
					fclose(VehiclesDB);
					tempfile = fopen("temp.txt", "r");
					VehiclesDB = fopen("VehiclesDB.txt", "w");
					struct VehicleObj vehicle1;
					while (fread(&vehicle1, sizeof(struct VehicleObj), 1, tempfile)) {
						if (vehicle1.prog_id == vehicle.prog_id) {

						}
						else {
							fwrite(&vehicle1, sizeof(struct VehicleObj), 1, VehiclesDB);
						}
					}
					fclose(tempfile);
					fclose(VehiclesDB);
					VehiclesDB = fopen("VehiclesDB.txt", "a");
					char sel1[13][30] = { "Classification", "Trim", "Automatic", "Milage", "Quantity", "Licence Plate", "Model Number", "Make", "Model Name", "Model Year" , "How Many Damage", "Rented", "Daily Price" };
					switch (cs) {
					case 0:
						strcpy(vehicle.classification, Question(sel1[0], 'q'));
						break;
					case 1:
						strcpy(vehicle.trim, Question(sel1[1], 'q'));
						break;
					case 2:
						if (strcmp(Question(sel1[2], 'y'), "yes") == 0) {
							vehicle.automatic = true;
						}
						else {
							vehicle.automatic = false;
						}
						break;
					case 3:
						vehicle.milage = Question(sel1[3]);
						break;
					case 4:
						vehicle.quantity = Question(sel1[4]);
						break;
					case 5:
						strcpy(vehicle.licenceplate, Question(sel1[5], 'q'));
						break;
					case 6:
						strcpy(vehicle.modelnumber, Question(sel1[6], 'q'));
						break;
					case 7:
						strcpy(vehicle.make, Question(sel1[7], 'q'));
						break;
					case 8:
						strcpy(vehicle.modelname, Question(sel1[8], 'q'));
						break;
					case 9:
						vehicle.modelyear = Question(sel1[9]);
						break;
					case 10:
						vehicle.damagetotal = 0;
						for (int i = 0; i < Question(sel1[10]); i++) {
							int vs = 16, hs = 17;
							DamagedObj cd1 = CarDamage(&vs, &hs, i+1);
							vehicle.damage[i] = cd1;
							vehicle.damagetotal++;
						}
						break;
					case 11:
						if (strcmp(Question(sel1[11], 'y'), "yes") == 0) {
							CustomerObj customerrented = SearchCustomer(true);
							RentedObj rented = { true, customerrented };
							vehicle.rented = rented;
						}
						else {
							RentedObj notrented = { false };
							vehicle.rented = notrented;
						}
						break;
					case 12:
						vehicle.price = Question(sel1[12]);
						break;
					case 13:
						back('v');
						break;
					}
					fwrite(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB);
					fclose(VehiclesDB);
				}
			}
			break;
		case 2:
			{
				system("cls");
				VehicleObj vehicle = SearchVehicle(true);
				FILE* tempfile = fopen("temp.txt", "w");
				VehiclesDB = fopen("VehiclesDB.txt", "r");
				char x = fgetc(VehiclesDB);
				while (x != EOF)
				{
					fputc(x, tempfile);
					x = fgetc(VehiclesDB);
				}
				fclose(tempfile);
				fclose(VehiclesDB);
				tempfile = fopen("temp.txt", "r");
				VehiclesDB = fopen("VehiclesDB.txt", "w");
				struct VehicleObj vehicle1;
				while (fread(&vehicle1, sizeof(struct VehicleObj), 1, tempfile)) {
					if (vehicle1.prog_id == vehicle.prog_id) {

					}
					else {
						fwrite(&vehicle1, sizeof(struct VehicleObj), 1, VehiclesDB);
					}
				}
				fclose(tempfile);
				fclose(VehiclesDB);
			}
			break;
		case 3:
			ManageDiscount();
			break;
		case 4:
			back('v');
			break;
	}
	printf("\n\n\n\nPress Enter To Continue...");
	while (true) {
		if (_kbhit()) {
			int i = _getch();
			if (i == 13) {
				back('v');
			}
		}
	}
}

void CarDamageSelector(int selector[2]) {
	char car[33][36] = {
"       ,***//(((((((((///**,.      ",
"    ./(/../((((((((((((((. *((,    ",
"   /(, ./((((((((((((((((((, ./(.  ",
"  ,(./((((((((((((((((((((((((.//  ",
"  *((((((((((((((((((((((((((((/(  ",
"  /((((((((((((((((((((((((((((((. ",
"  (((((((((((((((((((((((((((((((, ",
" .((((((((((/*********//(((((((((, ",
" .(((,                       .(((, ",
" .(((.                        /((, ",
"  /((,                        (((. ",
"./((((.......         .......*((((,",
"  /(*/((((((((((((((((((((((((.((. ",
"  /(,,(((((((((((((((((((((((/ ((. ",
"  ((, /((((((((((((((((((((((. ((, ",
" .((, ,(((((((((((((((((((((/  ((, ",
" .((, .(((((((((((((((((((((*  ((, ",
"  ((, .(((((((((((((((((((((*  ((, ",
"  /(*,/((((((((((((((((((((((*,((. ",
"  /(* .(((((((((((((((((((((* .((. ",
"  ((* .(((((((((((((((((((((* .((. ",
" .((/ .(((((((((((((((((((((* ,((, ",
" .((/ ,(((((((((((((((((((((/ *((, ",
" .((/,(((((((((((((((((((((((//((* ",
" .((((((,                  ((((((, ",
"  (((((/                   *(((((, ",
"  /((((*                   .(((((. ",
"  /((((.                    /((((. ",
"  *(((/                     ,((((  ",
"  .((((((((//**,,,,,***/((((((((*  ",
"   (//((((((((((((((((((((((((*(.  ",
"   ./.*(((((((((((((((((((((/./*   ",
"     ,/(((((((((((((((((((((/*.    ",
	};
	for (int i = 0; i < 33; i++) {
		for (int j = 0; j < 35; j++) {
			SetConsoleTextAttribute(hConsole, 15);
			if (selector[0] == j || selector[0] + 1 == j || selector[0] + 2 == j) {
				if (selector[1] == i || selector[1] + 1 == i || selector[1] + 2 == i) {
					SetConsoleTextAttribute(hConsole, 12);
				}
			}
			printf("%c", car[i][j]);
		}
		printf("\n");
	}
	SetConsoleTextAttribute(hConsole, 15);
}

DamagedObj CarDamage(int *vs, int *hs, int id) {
	system("MODE 100, 50");
	int selector[2] = { *hs,*vs };
	char title[30];
	sprintf(title, "Damage #%d", id);
	SetConsoleTextAttribute(hConsole, 6);
	if (sizeof(title) > 1) {
		int ret;
		ret = GetConsoleScreenBufferInfo(hConsole, &coninfo);
		if (ret)
		{
			int stringlength = strlen(title);
			int spacing = (coninfo.dwSize.X + stringlength) / 2;
			printf("%*s\n\n\n", spacing, title);
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
	Sleep(1000);
	system("cls");
	CarDamageSelector(selector);
	while (true) {
		if (_kbhit()) {

			int i = _getch();
			if (i == 224) {
				i = _getch();
				if (i == 72) {
					clear(0, 0);
					if ((*vs) - 1 >= 0) {
						(*vs)--;
					}
					else {
						(*vs) = 33 - 1;
					}
					int selector[2] = { *hs,*vs };
					CarDamageSelector(selector);
				}
				if (i == 80) {
					clear(0, 0);
					if ((*vs) + 1 < 33) {
						(*vs)++;
					}
					else {
						(*vs) = 0;
					}
					int selector[2] = { *hs,*vs };
					CarDamageSelector(selector);
				}
				if (i == 75) {
					clear(0, 0);
					if ((*hs) - 1 >= 0) {
						(*hs)--;
					}
					else {
						(*hs) = 33 - 1;
					}
					int selector[2] = { *hs,*vs };
					CarDamageSelector(selector);
				}
				if (i == 77) {
					clear(0, 0);
					if ((*hs) + 2 < 33) {
						(*hs)++;
					}
					else {
						(*hs) = 0;
					}
					int selector[2] = { *hs,*vs };
					CarDamageSelector(selector);
				}
			}
			if (i == 13) {
				DamagedObj dmgobj = { { *hs,*vs } };
				system("MODE 120, 40");
				return dmgobj;
			}
		}
	}
}

void ManageDiscount() {
	system("cls");
	char c[3][150] = { "Set Discount", "Remove Discount", "Back" };
	int cs = 0;
	char st[30] = "";
	Menu(cs, c, 3, st);
	Selection(&cs, c, 3, st);
	switch (cs) {
	case 0:
	{
		system("cls");
		VehicleObj vehicle = SearchVehicle(true);
		if (vehicle.prog_id > 0) {
			FILE* tempfile = fopen("temp.txt", "w");
			DiscountDB = fopen("DiscountDB.txt", "r");
			char x = fgetc(DiscountDB);
			while (x != EOF)
			{
				fputc(x, tempfile);
				x = fgetc(DiscountDB);
			}
			fclose(tempfile);
			fclose(DiscountDB);
			tempfile = fopen("temp.txt", "r");
			DiscountDB = fopen("DiscountDB.txt", "w");
			struct DiscountObj dicount;
			while (fread(&dicount, sizeof(struct DiscountObj), 1, tempfile)) {
				if (dicount.vehicle.prog_id == vehicle.prog_id) {

				}
				else {
					fwrite(&dicount, sizeof(struct DiscountObj), 1, DiscountDB);
				}
			}
			fclose(tempfile);
			fclose(DiscountDB);
			DiscountDB = fopen("DiscountDB.txt", "a");
			char sel1[1][30] = { "Discount" };
			printf("\n\n");
			float discountpercentage = Questionf(sel1[0]) / 100;
			dicount.vehicle = vehicle;
			dicount.discountpercentage = discountpercentage;
			fwrite(&dicount, sizeof(struct DiscountObj), 1, DiscountDB);
			fclose(DiscountDB);
			Sleep(500);
			int ret = GetConsoleScreenBufferInfo(hConsole, &coninfo);
			if (ret)
			{
				char txt[50];
				sprintf(txt, "Discount Set to %.2f %%", 100.00f*discountpercentage);
				int stringlength = strlen(txt);
				int spacing = (coninfo.dwSize.X + stringlength) / 2;
				printf("%*s\n\n\n", spacing, txt);
			}
		}
		break;
	}
	case 1:
	{
		system("cls");
		VehicleObj vehicle = SearchVehicle(true);
		if (vehicle.prog_id > 0) {
			FILE* tempfile = fopen("temp.txt", "w");
			DiscountDB = fopen("DiscountDB.txt", "r");
			char x = fgetc(DiscountDB);
			while (x != EOF)
			{
				fputc(x, tempfile);
				x = fgetc(DiscountDB);
			}
			fclose(tempfile);
			fclose(DiscountDB);
			tempfile = fopen("temp.txt", "r");
			DiscountDB = fopen("DiscountDB.txt", "w");
			struct VehicleObj vehicle1;
			while (fread(&vehicle1, sizeof(struct VehicleObj), 1, tempfile)) {
				if (vehicle1.prog_id == vehicle.prog_id) {

				}
				else {
					fwrite(&vehicle1, sizeof(struct VehicleObj), 1, DiscountDB);
				}
			}
			fclose(tempfile);
			fclose(DiscountDB);
			printf("Discount Removed");
		}
		break;
	}
	case 3:
		back('v');
		break;
	}
	printf("\n\n\n\nPress Enter To Continue...");
	while (true) {
		if (_kbhit()) {
			int i = _getch();
			if (i == 13) {
				back('v');
			}
		}
	}
}

void RecieveVehicle() {
	VehicleObj vehicle = SearchVehicle(true);
	if (vehicle.prog_id > 0) {
		if (!vehicle.rented.rented) {
			printf("Car is not rented");
			return;
		}
		system("cls");
		char sel1[2][40] = { "Do you wish to continue", "Does it have new Damage?" };
		CustomerObj customerrented = SearchCustomer(true);
		while (customerrented.prog_id > 0) {
			if (strcmp(Question(sel1[0], 'y'), "no") == 0) {
				return;
			}
			customerrented = SearchCustomer(true);
		}
		int damagecount = Question(sel1[1]);
		for (int i = 0; i < damagecount; i++) {
			int vs = 16, hs = 17;
			DamagedObj cd1 = CarDamage(&vs, &hs, i + 1);
			vehicle.damage[i - 1 + vehicle.damagetotal] = cd1;
		}
		if (damagecount > 0) {
			SetConsoleTextAttribute(hConsole, 6);
			printTitle();
			SetConsoleTextAttribute(hConsole, 15);
			printf("Please Pay Amount Due to Damage");
			while (true) {
				if (Pay(((vehicle.price * 0.1) * damagecount))) {
					system("cls");
					break;
				}
			}
		}
		FILE* tempfile = fopen("temp.txt", "w");
		VehiclesDB = fopen("VehiclesDB.txt", "r");
		char x = fgetc(VehiclesDB);
		while (x != EOF)
		{
			fputc(x, tempfile);
			x = fgetc(VehiclesDB);
		}
		fclose(tempfile);
		fclose(VehiclesDB);
		tempfile = fopen("temp.txt", "r");
		VehiclesDB = fopen("VehiclesDB.txt", "w");
		struct VehicleObj vehicle1;
		while (fread(&vehicle1, sizeof(struct VehicleObj), 1, tempfile)) {
			if (vehicle1.prog_id == vehicle.prog_id) {

			}
			else {
				fwrite(&vehicle1, sizeof(struct VehicleObj), 1, VehiclesDB);
			}
		}
		fclose(tempfile);
		fclose(VehiclesDB);
		VehiclesDB = fopen("VehiclesDB.txt", "a");
		RentedObj rented = { false };
		vehicle.rented = rented;
		fwrite(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB);
		fclose(VehiclesDB);
	}
}

void RentVehicle() {
	system("cls");
	VehicleObj vehicle = SearchVehicle(true);
	if (vehicle.prog_id > 0) {
		system("cls");
		if (vehicle.rented.rented) {
			printf("\n\nVehicle Already Rented");
			printf("\n\n\n\nPress Enter To Continue...");
			while (true) {
				if (_kbhit()) {
					int i = _getch();
					if (i == 13) {
						back('v');
					}
				}
			}
		}
		char sel1[4][50] = { "Do you wish to continue" , "" , "Do you want to create a new Customer", "how many days"};
		sprintf(sel1[1], "There Is %d Damages Do you want to show the damage?", vehicle.damagetotal);
		if (vehicle.damagetotal > 0) {
			if (strcmp(Question(sel1[1], 'y'), "no") == 0) {
				for (int i = 0; i < vehicle.damagetotal; i++) {
					system("MODE 100, 50");
					char title[30];
					sprintf(title, "Damage #%d", i+1);
					SetConsoleTextAttribute(hConsole, 6);
					if (sizeof(title) > 1) {
						int ret;
						ret = GetConsoleScreenBufferInfo(hConsole, &coninfo);
						if (ret)
						{
							int stringlength = strlen(title);
							int spacing = (coninfo.dwSize.X + stringlength) / 2;
							printf("%*s\n\n\n", spacing, title);
						}
					}
					SetConsoleTextAttribute(hConsole, 15);
					Sleep(1000);
					DamagedObj damage = vehicle.damage[i];
					CarDamageSelector(damage.coordinate);
					printf("\n\n\n\nPress Enter To Continue...");
					while (true) {
						if (_kbhit()) {
							int i = _getch();
							if (i == 13) {
								break;
							}
						}
					}
				}
				system("MODE 120, 40");
			}
			printTitle();
			int days = Question(sel1[3]);
			DiscountDB = fopen("DiscountDB.txt", "r");
			DiscountObj dicount;
			while (fread(&dicount, sizeof(struct DiscountObj), 1, DiscountDB)) {
				if (dicount.vehicle.prog_id == vehicle.prog_id) {
					vehicle.price = vehicle.price - (vehicle.price * dicount.discountpercentage);
					printf("\n\nYou Have Been Discounted %.2f", (((float)vehicle.price) * dicount.discountpercentage));
				}
			}
			fclose(DiscountDB);
			vehicle.price *= days;
			printf("\n\nThe Total Price Will Be %.2f S.R\n\n", vehicle.price);
			if (strcmp(Question(sel1[0], 'y'), "no") == 0) {
				return;
			}
		}
		CustomerObj customerrented;
		if (strcmp(Question(sel1[2], 'y'), "no") == 0) {
			customerrented = SearchCustomer(true);
			while (customerrented.prog_id <= 0) {
				if (strcmp(Question(sel1[2], 'y'), "no") == 0) {
					customerrented = CreateCustomer();
					break;
				}
				customerrented = SearchCustomer(true);
			}
		}
		else {
			customerrented = CreateCustomer();
		}
		if (Pay(vehicle.price)) {
			system("cls");
			FILE* tempfile = fopen("temp.txt", "w");
			VehiclesDB = fopen("VehiclesDB.txt", "r");
			char x = fgetc(VehiclesDB);
			while (x != EOF)
			{
				fputc(x, tempfile);
				x = fgetc(VehiclesDB);
			}
			fclose(tempfile);
			fclose(VehiclesDB);
			tempfile = fopen("temp.txt", "r");
			VehiclesDB = fopen("VehiclesDB.txt", "w");
			struct VehicleObj vehicle1;
			while (fread(&vehicle1, sizeof(struct VehicleObj), 1, tempfile)) {
				if (vehicle1.prog_id == vehicle.prog_id) {
					vehicle1.rented.rented = true;
					vehicle1.rented.customer = customerrented;
					fwrite(&vehicle1, sizeof(struct VehicleObj), 1, VehiclesDB);
				}
				else {
					fwrite(&vehicle1, sizeof(struct VehicleObj), 1, VehiclesDB);
				}
			}
			fclose(tempfile);
			fclose(VehiclesDB);
			VehiclesDB = fopen("VehiclesDB.txt", "a");
			RentedObj rented = { true, customerrented };
			vehicle.rented = rented;
			fwrite(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB);
			fclose(VehiclesDB);
		}
		printf("\n\n\n\nPress Enter To Continue...");
		while (true) {
			if (_kbhit()) {
				int i = _getch();
				if (i == 13) {
					back('v');
				}
			}
		}
	}
}

VehicleObj SearchVehicle(bool select) {
	system("cls");
	char c[7][150] = { "By Classification", "By Millage", "By Quantity", "By Model Year + Model Name + Make", "By License plate Number", "By Customer Renting", "Back" };
	int cs = 0;
	char st[30] = "Search Vehicle";
	Menu(cs, c, 5, st);
	Selection(&cs, c, 5, st);
	system("cls");
	SetConsoleTextAttribute(hConsole, 6);
	printTitle();
	SetConsoleTextAttribute(hConsole, 15);
	VehiclesDB = fopen("VehiclesDB.txt", "r");
	struct VehicleObj vehicle;
	char cse[7][50] = { "Classification", "Millage", "Quantity", "Model Year", "Model Name" ,"Make", "License plate Number"};
	bool found = false;
	VehicleObj vehiclelist[30]{};
	int i = 0;
	switch (cs) {
	case 0:
		char classifcation[90];
		strcpy(classifcation, Question(cse[0], 'q'));
		for (int j = 0; classifcation[j]; j++) {
			classifcation[j] = tolower(classifcation[j]);
		}
		while (fread(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB)) {
			if (strcmp(vehicle.classification,classifcation) == 0) {
				found = true;
				printf("\n\n\nClassification = %s \nTrim = %s \nAutomatic = %s\n", vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False");
				printf("HasDamage = %s \nMilage = %d \nQuatity = %d\n", (vehicle.damagetotal > 0) ? "True" : "False", vehicle.milage, vehicle.quantity);
				printf("Rented = %s \nLicence Plate = %s \nModel Number = %s\n", (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber);
				printf("Make = %s \nModel Year = %d \nModel Name = %s \nDaily Price = %f\n", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
				vehiclelist[i] = vehicle;
				i++;
			}
		}
		break;
	case 1:
		int Milage;
		Milage = Question(cse[1]);
		while (fread(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB)) {
			if (vehicle.milage == Milage) {
				found = true;
				printf("\n\n\nClassification = %s \nTrim = %s \nAutomatic = %s\n", vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False");
				printf("HasDamage = %s \nMilage = %d \nQuatity = %d\n", (vehicle.damagetotal > 0) ? "True" : "False", vehicle.milage, vehicle.quantity);
				printf("Rented = %s \nLicence Plate = %s \nModel Number = %s\n", (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber);
				printf("Make = %s \nModel Year = %d \nModel Name = %s \nDaily Price = %f\n", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
				vehiclelist[i] = vehicle;
				i++;
			}
		}
		break;
	case 2:
		int Quatity;
		Quatity = Question(cse[2]);
		while (fread(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB)) {
			if (vehicle.quantity == Quatity) {
				found = true;
				printf("\n\n\nClassification = %s \nTrim = %s \nAutomatic = %s\n", vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False");
				printf("HasDamage = %s \nMilage = %d \nQuatity = %d\n", (vehicle.damagetotal > 0) ? "True" : "False", vehicle.milage, vehicle.quantity);
				printf("Rented = %s \nLicence Plate = %s \nModel Number = %s\n", (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber);
				printf("Make = %s \nModel Year = %d \nModel Name = %s \nDaily Price = %f\n", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
				vehiclelist[i] = vehicle;
				i++;
			}
		}
		break;
	case 3:
		int ModelYear;
		char ModelName[30];
		char Make[30];
		ModelYear = Question(cse[3]);
		strcpy(ModelName, Question(cse[4], 'q'));
		for (int j = 0; ModelName[j]; j++) {
			ModelName[j] = tolower(ModelName[j]);
		}
		strcpy(Make, Question(cse[5], 'q'));
		for (int j = 0; Make[j]; j++) {
			Make[j] = tolower(Make[j]);
		}
		while (fread(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB)) {
			if (vehicle.modelyear == ModelYear && strcmp(vehicle.modelname, ModelName) == 0 && strcmp(vehicle.make, Make) == 0) {
				found = true;
				printf("\n\n\nClassification = %s \nTrim = %s \nAutomatic = %s\n", vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False");
				printf("HasDamage = %s \nMilage = %d \nQuatity = %d\n", (vehicle.damagetotal > 0) ? "True" : "False", vehicle.milage, vehicle.quantity);
				printf("Rented = %s \nLicence Plate = %s \nModel Number = %s\n", (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber);
				printf("Make = %s \nModel Year = %d \nModel Name = %s \nDaily Price = %f\n", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
				vehiclelist[i] = vehicle;
				i++;
			}
		}
		break;
	case 4:
		char licenceplate[20];
		strcpy(licenceplate, Question(cse[6], 'q'));
		for (int j = 0; licenceplate[j]; j++) {
			licenceplate[j] = tolower(licenceplate[j]);
		}
		while (fread(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB)) {
			if (strcmp(vehicle.licenceplate, licenceplate) == 0) {
				found = true;
				printf("\n\n\nClassification = %s \nTrim = %s \nAutomatic = %s\n", vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False");
				printf("HasDamage = %s \nMilage = %d \nQuatity = %d\n", (vehicle.damagetotal > 0) ? "True" : "False", vehicle.milage, vehicle.quantity);
				printf("Rented = %s \nLicence Plate = %s \nModel Number = %s\n", (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber);
				printf("Make = %s \nModel Year = %d \nModel Name = %s \nDaily Price = %f\n", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
				vehiclelist[i] = vehicle;
				i++;
			}
		}
		break;
	case 5:
		RentedObj rented;
		CustomerObj customerrented = SearchCustomer(true);
		rented = { true, customerrented };
		while (fread(&vehicle, sizeof(struct VehicleObj), 1, VehiclesDB)) {
			if (vehicle.rented.rented == rented.rented && vehicle.rented.customer.prog_id == rented.customer.prog_id) {
				found = true;
				printf("\n\n\nClassification = %s \nTrim = %s \nAutomatic = %s\n", vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False");
				printf("HasDamage = %s \nMilage = %d \nQuatity = %d\n", (vehicle.damagetotal > 0) ? "True" : "False", vehicle.milage, vehicle.quantity);
				printf("Rented = %s \nLicence Plate = %s \nModel Number = %s\n", (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber);
				printf("Make = %s \nModel Year = %d \nModel Name = %s \nDaily Price = %f\n", vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
				vehiclelist[i] = vehicle;
				i++;
			}
		}
		break;
	case 6:
		fclose(VehiclesDB);
		back('c');
		break;
	}
	const int size = i;
	if (!found) {
		printf("\n\nNo Vehicle With These Credentials was found");
	}
	else if (select && size > 1) {
		char c[30][150];
		memset(c, 0, sizeof c);
		for (int j = 0; j < size; j++) {
			sprintf(c[j],  "Classification = (%s) Trim = (%s) Automatic = (%s) HasDamage = (%s) Milage = (%d) Quatity = (%d) Rented = (%s) Licence Plate = (%s) Model Number = (%s) Make = (%s) Model Year = (%d) Model Name = (%s) Daily Price = (%f)",
				vehicle.classification, vehicle.trim, (vehicle.automatic) ? "True" : "False", (vehicle.damage) ? "True" : "False", vehicle.milage,vehicle.quantity, (vehicle.rented.rented) ? "True" : "False", vehicle.licenceplate, vehicle.modelnumber, vehicle.make, vehicle.modelyear, vehicle.modelname, vehicle.price);
		}
		char st[30] = "Which one?";

		system("cls");
		menu(cs, c, size, st, false);
		selection(&cs, c, size, 0, 0, st, false);
		fclose(VehiclesDB);
		return vehiclelist[cs];
	}
	else {
		char sel1[2][50] = { "", "Do you want to show the car image" };
		if (vehicle.damagetotal > 0) {
			printf("\n\n");
			sprintf(sel1[0], "There Is %d Damages Do you want to show the damage?", vehicle.damagetotal);
			if (strcmp(Question(sel1[0], 'y'), "yes") == 0) {
				for (int i = 0; i < vehicle.damagetotal; i++) {
					system("MODE 100, 50");
					char title[30];
					sprintf(title, "Damage #%d", i + 1);
					SetConsoleTextAttribute(hConsole, 6);
					if (sizeof(title) > 1) {
						int ret;
						ret = GetConsoleScreenBufferInfo(hConsole, &coninfo);
						if (ret)
						{
							int stringlength = strlen(title);
							int spacing = (coninfo.dwSize.X + stringlength) / 2;
							printf("%*s\n\n\n", spacing, title);
						}
					}
					SetConsoleTextAttribute(hConsole, 15);
					Sleep(1000);
					DamagedObj damage = vehicle.damage[i];
					CarDamageSelector(damage.coordinate);
					printf("\n\n\n\nPress Enter To Continue...");
					while (true) {
						if (_kbhit()) {
							int i = _getch();
							if (i == 13) {
								break;
							}
						}
					}
				}
				system("MODE 120, 40");
			}
		}
		printf("\n\n");
		if (strcmp(Question(sel1[1], 'y'), "yes") == 0) {
			char apicall[300];
			sprintf(apicall, "powershell -noexit -command \"start %s.png; exit 0\" ", vehicle.modelnumber);
			system(apicall);
		}
	}
	return vehiclelist[0];
}

bool Pay(float price) {
	system("cls");
	char c[3][150] = { "Card", "Cash" , "Back" };
	int cs = 0;
	char st[30] = "Do You Want To Pay With";
	Menu(cs, c, 3, st);
	Selection(&cs, c, 3, st);
	char sel1[6][50] = { "Payment Amount" , "Card No", "Exp Month (MM)", "Exp Year (YYYY)", "CVV", "Do you want to try again?" };
	float paid = 0;
	switch (cs) {
		case 0:
			while (paid < price) {
				char cardno[11];
				strcpy(cardno,Question(sel1[1], 'q'));
				int endmonth = Question(sel1[2]);
				int endyear = Question(sel1[3]);
				int cvv = Question(sel1[4]);
				bool accepted = false;
				if (endyear > 2021 || (endyear == 2021 && endmonth > 4)) {
					accepted = true;
				}
				if (accepted) {
					paid = Questionf(sel1[0]);
					if (paid > price) {
						printf("\n\n You Have Been Refunded %f", price - paid);
					}
				}
				else {
					printf("Your Card Has Been Declined");
					if (strcmp(Question(sel1[5], 'y'), "no") == 0) {
						return false;
					}
				}
			}
			break;
		case 1:
			while (paid < price) {
				paid = Questionf(sel1[0]);
				if (paid > price) {
					printf("\n\n You Have Been Refunded %f", price - paid);
				}
			}
			return true;
			break;
		case 2:
			return false;
	}
}

void Customer() {
	system("cls");
	char c[3][150] = { "Manage Customer", "Search Customer", "Back" };
	int cs = 0;
	char st[30] = "";
	Menu(cs, c, 3, st);
	Selection(&cs, c, 3, st);
	switch (cs) {
	case 0:
		ManageCustomer();
		break;
	case 1:
		SearchCustomer(false);
		printf("\n\n\n\nPress Enter To Continue...");
		while (true) {
			if (_kbhit()) {
				int i = _getch();
				if (i == 13) {
					back('c');
				}
			}
		}
	case 2:
		back('m');
	}
}

void ManageCustomer() {
	system("cls");
	char c[4][150] = { "Add Customer", "Edit Customer", "Manage Blacklist", "Back" };
	int cs = 0;
	char st[30] = "";
	Menu(cs, c, 4, st);
	Selection(&cs, c, 4, st);
	int ret = GetConsoleScreenBufferInfo(hConsole, &coninfo);
	char sel1[8][30] = { "ID", "Name", "Phone Number", "Age", "Emergency Number", "Email", "Address", "Gender" };
	switch (cs) {
		case 0:
		{
			CreateCustomer();
			if (ret)
			{
				int stringlength = strlen("Customer Added");
				int spacing = (coninfo.dwSize.X + stringlength) / 2;
				printf("%*s\n\n\n", spacing, "Customer Added");
			}
			break;
		}
		case 1:
		{
			system("cls");
			system("MODE 150, 50");
			CustomerObj customer = SearchCustomer(true);
			if (customer.prog_id > 0) {
				char c[9][150] = { "ID", "Name", "Phone Number", "Age", "Emergency Number", "Email", "Address", "Gender", "back" };
				int cs = 0;
				char st[30] = "Search Customer";
				Menu(cs, c, 9, st);
				Selection(&cs, c, 9, st);
				system("MODE 120, 30");
				FILE* tempfile = fopen("temp.txt", "w");
				CustomersDB = fopen("CustomersDB.txt", "r");
				char x = fgetc(CustomersDB);
				while (x != EOF)
				{
					fputc(x, tempfile);
					x = fgetc(CustomersDB);
				}
				fclose(tempfile);
				fclose(CustomersDB);
				tempfile = fopen("temp.txt", "r");
				CustomersDB = fopen("CustomersDB.txt", "w");
				struct CustomerObj customer1;
				while (fread(&customer1, sizeof(struct CustomerObj), 1, tempfile)) {
					if (customer1.prog_id == customer.prog_id) {

					}
					else {
						fwrite(&customer1, sizeof(struct CustomerObj), 1, CustomersDB);
					}
				}
				fclose(tempfile);
				fclose(CustomersDB);
				BlacklistDB = fopen("BlacklistDB.txt", "r");
				bool inbl = false;
				while (fread(&customer1, sizeof(struct CustomerObj), 1, BlacklistDB)) {
					if (customer1.prog_id == customer.prog_id) {
						FILE* tempfile2 = fopen("temp2.txt", "w");
						char x = fgetc(CustomersDB);
						while (x != EOF)
						{
							fputc(x, tempfile2);
							x = fgetc(CustomersDB);
						}
						fclose(tempfile2);
						fclose(BlacklistDB);
						tempfile2 = fopen("temp2.txt", "r");
						BlacklistDB = fopen("BlacklistDB.txt", "w");
						struct CustomerObj customer1;
						while (fread(&customer1, sizeof(struct CustomerObj), 1, tempfile2)) {
							if (customer1.prog_id == customer.prog_id) {

							}
							else {
								fwrite(&customer1, sizeof(struct CustomerObj), 1, BlacklistDB);
							}
						}
						fclose(tempfile2);
						fclose(BlacklistDB);
						inbl = true;
					}
				}
				CustomersDB = fopen("CustomersDB.txt", "a");
				BlacklistDB = fopen("BlacklistDB.txt", "a");
				switch (cs) {
				case 0:
					customer.ID = Question(sel1[0]);
					break;
				case 1:
					strcpy(customer.Name, Question(sel1[1], 'q'));
					break;
				case 2:
					customer.PhoneNo = Question(sel1[2]);
					break;
				case 3:
					customer.Age = Question(sel1[3]);
					break;
				case 4:
					customer.EmergencyNo = Question(sel1[4]);
					break;
				case 5:
					strcpy(customer.Email, Question(sel1[5], 'q'));
					break;
				case 6:
					strcpy(customer.Address, Question(sel1[6], 'q'));
					break;
				case 7:
					strcpy(customer.Gender, Question(sel1[7], 'm'));
					break;
				case 8:
					back('c');
					break;
				}
				if (inbl) {
					fwrite(&customer, sizeof(struct CustomerObj), 1, BlacklistDB);
					fclose(BlacklistDB);
				}
				fwrite(&customer, sizeof(struct CustomerObj), 1, CustomersDB);
				fclose(CustomersDB);
			}
			break;
		}
		case 2:
		{
			system("cls");
			char cx[4][150] = { "Show List", "Add to List", "Remove from List", "Back" };
			int csx = 0;
			char stx[30] = "";
			Menu(csx, cx, 4, stx);
			Selection(&csx, cx, 4, stx);
			switch (csx) {
			case 0:
			{
				struct CustomerObj customer1;
				BlacklistDB = fopen("BlacklistDB.txt", "r");
				while (fread(&customer1, sizeof(struct CustomerObj), 1, BlacklistDB)) {
					printf("========================================================================");
					printf("\n\n ID = %d\n Name = %s\n PhoneNo = %d\n", customer1.ID, customer1.Name,
						customer1.PhoneNo);
					printf(" Age = %d\n EmergencyNo = %d\n Email = %s\n", customer1.Age, customer1.EmergencyNo,
						customer1.Email);
					printf(" Address = %s\n Gender = %s\n", customer1.Address, customer1.Gender);
					printf("========================================================================");
				}
				fclose(BlacklistDB);
				printf("\n\n\n\nPress Enter To Continue...");
				while (true) {
					if (_kbhit()) {
						int i = _getch();
						if (i == 13) {
							back('c');
						}
					}
				}
			}
				break;
			case 1:
			{
				CustomerObj customer = SearchCustomer(true);
				struct CustomerObj customer1;
				struct CustomerObj empty = { 0 };
				if (customer.prog_id != empty.prog_id) {
					BlacklistDB = fopen("BlacklistDB.txt", "r");
					while (fread(&customer1, sizeof(struct CustomerObj), 1, BlacklistDB)) {
						if (customer1.prog_id == customer.prog_id) {
							printf("Customer Already in BlackList");
							printf("\n\n\n\nPress Enter To Continue...");
							while (true) {
								if (_kbhit()) {
									int i = _getch();
									if (i == 13) {
										fclose(BlacklistDB);
										back('c');
									}
								}
							}
						}
					}
					fclose(BlacklistDB);
					BlacklistDB = fopen("BlacklistDB.txt", "a");
					fwrite(&customer, sizeof(struct CustomerObj), 1, BlacklistDB);
					fclose(BlacklistDB);
					printf("Customer Added To BlackList");
				}
				printf("\n\n\n\nPress Enter To Continue...");
				while (true) {
					if (_kbhit()) {
						int i = _getch();
						if (i == 13) {
							back('c');
						}
					}
				}
			}
				break;
			case 2:
			{
				CustomerObj customer = SearchCustomer(true);
				struct CustomerObj customer1;
				BlacklistDB = fopen("BlacklistDB.txt", "r");
				bool inbl = false;
				while (fread(&customer1, sizeof(struct CustomerObj), 1, BlacklistDB)) {
					if (customer1.prog_id == customer.prog_id) {
						FILE* tempfile2 = fopen("temp2.txt", "w");
						char x = fgetc(CustomersDB);
						while (x != EOF)
						{
							fputc(x, tempfile2);
							x = fgetc(CustomersDB);
						}
						fclose(tempfile2);
						fclose(BlacklistDB);
						tempfile2 = fopen("temp2.txt", "r");
						BlacklistDB = fopen("BlacklistDB.txt", "w");
						struct CustomerObj customer1;
						while (fread(&customer1, sizeof(struct CustomerObj), 1, tempfile2)) {
							if (customer1.prog_id == customer.prog_id) {

							}
							else {
								fwrite(&customer1, sizeof(struct CustomerObj), 1, BlacklistDB);
							}
						}
						fclose(tempfile2);
						fclose(BlacklistDB);
						inbl = true;
					}
				}
				if (inbl) {
					printf("Customer Removed From Blacklist");
				}
				else {
					printf("Customer Not In Blacklist");
				}
				printf("\n\n\n\nPress Enter To Continue...");
				while (true) {
					if (_kbhit()) {
						int i = _getch();
						if (i == 13) {
							back('c');
						}
					}
				}
			}
				break;
			case 3:
				back('c');
				break;
			}
			back('c');
			break;
		}
		case 3:
			back('c');
			break;
	}
	printf("\n\n\n\nPress Enter To Continue...");
	while (true) {
		if (_kbhit()) {
			int i = _getch();
			if (i == 13) {
				back('c');
			}
		}
	}
}

CustomerObj CreateCustomer() {
	char sel1[8][30] = { "ID", "Name", "Phone Number", "Age", "Emergency Number", "Email", "Address", "Gender" };
	CustomersDB = fopen("CustomersDB.txt", "a");
	system("cls");
	SetConsoleTextAttribute(hConsole, 6);
	printTitle();
	SetConsoleTextAttribute(hConsole, 15);
	struct CustomerObj customer1;
	customer1.ID = Question(sel1[0]);
	strcpy(customer1.Name, Question(sel1[1], 'q'));
	customer1.PhoneNo = Question(sel1[2]);
	customer1.Age = Question(sel1[3]);
	if (customer1.Age < 25 || customer1.Age > 60) {
		system("cls");
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		system("title The Car Rental App");
		SetConsoleTextAttribute(hConsole, 12);
		printf("  _________                           \n");
		printf(" /   _____/ __________________ ___.__.\n");
		printf(" \\_____  \\ /  _ \\_  __ \\_  __ <   |  |\n");
		printf(" /        (  <_> )  | \\/|  | \\/\\___  |\n");
		printf("/_______  /\____/|__|   |__|   / ____|\n");
		printf("        \\/                     \\/     \n");
		printf("_____.___.                 _____                 \n");
		printf("\\__  |   | ____  __ __    /  _  \\_______   ____  \n");
		printf(" /   |   |/  _ \\|  |  \\  /  /_\\  \\_  __ \\_/ __ \\ \n");
		printf(" \\____   (  <_> )  |  / /    |    \\  | \\/\\  ___/ \n");
		printf(" / ______|\\____/|____/  \\____|__  /__|    \\___  >\n");
		printf(" \\/                             \\/            \\/ \n");
		printf("_____.___.                 _____                 \n");
		printf("\\__  |   | ____  __ __    /  _  \\_______   ____  \n");
		printf(" /   |   |/  _ \\|  |  \\  /  /_\\  \\_  __ \\_/ __ \\ \n");
		printf(" \\____   (  <_> )  |  / /    |    \\  | \\/\\  ___/ \n");
		printf(" / ______|\\____/|____/  \\____|__  /__|    \\___  >\n");
		printf(" \\/                             \\/            \\/ \n");
		printf("   _____                .__  .__             ___.   .__          \n");
		printf("  /  _  \\ ______ ______ |  | |__| ____ _____ \\_ |__ |  |   ____  \n");
		printf(" /  /_\\  \\\\____ \\\\____ \\|  | |  |/ ___\\\\__  \\ | __ \\|  | _/ __ \\ \n");
		printf("/    |    \\  |_> >  |_> >  |_|  \\  \\___ / __ \\| \\_\\ \\  |_\\  ___/ \n");
		printf("\\____|__  /   __/|   __/|____/__|\\___  >____  /___  /____/\\___  >\n");
		printf("        \\/|__|   |__|                \\/     \\/    \\/          \\/ \n\n\n\n");
		SetConsoleTextAttribute(hConsole, 15);
		printf("\n\n\n\nEnd The Program...");
		while (true) {
			if (_kbhit()) {
				int i = _getch();
				if (i == 13) {
					exit(0);
				}
			}
		}	
	}
	customer1.EmergencyNo = Question(sel1[4]);
	strcpy(customer1.Email, Question(sel1[5], 'q'));
	strcpy(customer1.Address, Question(sel1[6], 'q'));
	strcpy(customer1.Gender, Question(sel1[7], 'm'));
	maxcid++;
	customer1.prog_id = maxcid;
	fwrite(&customer1, sizeof(struct CustomerObj), 1, CustomersDB);
	fclose(CustomersDB);
	Sleep(500);
	return customer1;
}

CustomerObj SearchCustomer(bool select) {
	system("cls");
	char c[4][150] = { "By ID", "By Name", "By Phone Number", "By Email"};
	int cs = 0;
	char st[30] = "Search Customer";
	Menu(cs, c, 4, st);
	Selection(&cs, c, 4, st);
	system("cls");
	SetConsoleTextAttribute(hConsole, 6);
	printTitle();
	SetConsoleTextAttribute(hConsole, 15);
	CustomersDB = fopen("CustomersDB.txt", "r");
	struct CustomerObj customer1;
	char cse[4][30] = { "ID", "Name", "Phone Number", "Email"};
	bool found = false;
	CustomerObj customerlist[30]{};
	int i = 0;
	switch (cs) {
		case 0:
			int searchid;
			searchid = Question(cse[0]);
			while (fread(&customer1, sizeof(struct CustomerObj), 1, CustomersDB)) {
				if (customer1.ID == searchid) {
					found = true;
					printf("\n\n ID = %d\n Name = %s\n PhoneNo = %d\n", customer1.ID, customer1.Name,
						customer1.PhoneNo);
					printf(" Age = %d\n EmergencyNo = %d\n Email = %s\n", customer1.Age, customer1.EmergencyNo,
						customer1.Email);
					printf(" Address = %s\n Gender = %s\n", customer1.Address, customer1.Gender);
					customerlist[i] = customer1;
					i++;
				}
			}
			break;
		case 1:
			char searchname[30];
			strcpy(searchname,Question(cse[1], 'q'));
			for (int j = 0; searchname[j]; j++) {
				searchname[j] = tolower(searchname[j]);
			}
			while (fread(&customer1, sizeof(struct CustomerObj), 1, CustomersDB)) {
				if (strcmp(customer1.Name,searchname) == 0) {
					found = true;
					printf("\n\n ID = %d\n Name = %s\n PhoneNo = %d\n", customer1.ID, customer1.Name,
						customer1.PhoneNo);
					printf(" Age = %d\n EmergencyNo = %d\n Email = %s\n", customer1.Age, customer1.EmergencyNo,
						customer1.Email);
					printf(" Address = %s\n Gender = %s\n", customer1.Address, customer1.Gender);
					customerlist[i] = customer1;
					i++;
				}
			}
			break;
		case 2:
			int searchphone;
			searchphone = Question(cse[2]);
			while (fread(&customer1, sizeof(struct CustomerObj), 1, CustomersDB)) {
				if (customer1.PhoneNo == searchphone) {
					found = true;
					printf("\n\n ID = %d\n Name = %s\n PhoneNo = %d\n", customer1.ID, customer1.Name,
						customer1.PhoneNo);
					printf(" Age = %d\n EmergencyNo = %d\n Email = %s\n", customer1.Age, customer1.EmergencyNo,
						customer1.Email);
					printf(" Address = %s\n Gender = %s\n", customer1.Address, customer1.Gender);
					customerlist[i] = customer1;
					i++;
				}
			}
			break;
		case 3:
			char searchemail [30] ;
			strcpy(searchemail, Question(cse[3], 'q'));
			for (int j = 0; searchemail[j]; j++) {
				searchemail[j] = tolower(searchemail[j]);
			}
			while (fread(&customer1, sizeof(struct CustomerObj), 1, CustomersDB)) {
				if (strcmp(customer1.Email, searchemail) == 0) {
					found = true;
					printf("\n\n ID = %d\n Name = %s\n PhoneNo = %d\n", customer1.ID, customer1.Name,
						customer1.PhoneNo);
					printf(" Age = %d\n EmergencyNo = %d\n Email = %s\n", customer1.Age, customer1.EmergencyNo,
						customer1.Email);
					printf(" Address = %s\n Gender = %s\n", customer1.Address, customer1.Gender);
					customerlist[i] = customer1;
					i++;
				}
			}
			break;
	}
	const int size = i;
	if (!found) {
		printf("\n\nNo Customer With These Credentials was found");
	}
	else if (select && size > 1) {
		char c[30][150];
		memset(c, 0, sizeof c);
		for (int j = 0; j < size; j++) {
			sprintf(c[j],"ID = (%d) Name = (%s) PhoneNo = (%d) \nAge = (%d) EmergencyNo = (%d) Email = (%s) Address = (%s) Gender = (%s)" ,
				customerlist[j].ID, customerlist[j].Name, customerlist[j].PhoneNo, customerlist[j].Age,
				customerlist[j].EmergencyNo, customerlist[j].Email, customerlist[j].Address, customerlist[j].Gender);
		}
		char st[30] = "Which one?";

		system("cls");
		menu(cs, c, size, st, false);
		selection(&cs, c, size,0,0, st, false);
		return customerlist[cs];
	}
	return customerlist[0];
}
