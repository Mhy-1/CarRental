# Car Rental System

A comprehensive console-based car rental management system written in C++. The system provides a complete solution for managing vehicle rentals, customer information, and rental transactions.

## Features

### Vehicle Management
- Add, edit, and remove vehicles
- Track vehicle details:
  - Classification and trim
  - Transmission type (automatic/manual)
  - Mileage tracking
  - Vehicle quantity management
  - License plate and model information
  - Damage tracking with visual interface
  - Rental status monitoring
- Vehicle search functionality by:
  - Classification
  - Mileage
  - Quantity
  - Model details (year, name, make)
  - License plate
  - Current renter

### Customer Management
- Complete customer database with:
  - Personal information (name, ID, age)
  - Contact details (phone, email, address)
  - Emergency contact information
  - Gender
- Customer search functionality
- Blacklist management for problematic customers
- Age verification (25-60 years)

### Rental Operations
- Vehicle rental processing
- Damage inspection and reporting
- Payment processing:
  - Credit card payments
  - Cash payments
  - Refund calculation
- Multiple payment validation methods
- Rental return processing

### Additional Features
- Discount management system
- Visual damage marking interface
- Automated age verification
- Digital payment processing
- File-based data persistence
- User-friendly console interface
- Interactive menu navigation

## Technical Details

### Built With
- C++
- Windows Console API
- File I/O for data persistence

### Data Storage
- Customer database
- Vehicle database
- Blacklist database
- Discount database

### User Interface
- Interactive console menus
- Visual damage marking system
- Color-coded interface elements
- Keyboard navigation support

## Installation

1. Clone the repository
```bash
git clone https://github.com/yourusername/car-rental-system.git
```

2. Compile the source code using a C++ compiler
```bash
g++ main.cpp -o car_rental
```

3. Run the executable
```bash
./car_rental
```

## Usage

### Main Menu Navigation
- Use arrow keys to navigate menus
- Press Enter to select options
- Follow on-screen prompts for data entry

### Vehicle Management
1. Select "Vehicle" from main menu
2. Choose desired operation:
   - Manage Vehicle
   - Receive Rented Vehicle
   - Search Vehicle
   - Rent Vehicle

### Customer Management
1. Select "Customer" from main menu
2. Choose desired operation:
   - Manage Customer
   - Search Customer

### Rental Process
1. Select "Rent Vehicle"
2. Search for available vehicle
3. Enter customer information
4. Process payment
5. Confirm rental

## Contributing
Contributions are welcome. Please feel free to submit a Pull Request.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Authors
- Saud Fawaz Alshareef
- Mshari Ali Dajam
- Omar Baflh

## Acknowledgments
- Dr. Muhammad Usman Ilyas for project supervision
