// MainWindow.cpp
#include "MainWindow.h"
#include <QInputDialog>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      selectedMedicineIndex(0) {
    // Central widget setup
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Title
    QLabel *titleLabel = new QLabel("Medicine Vending Machine", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel, 0, 0, 1, 2);

    // Medicine selection dropdown
    medicineComboBox = new QComboBox(this);
    for (int i = 0; i < 5; ++i) {
        medicineComboBox->addItem(medicines[i].name);
    }
    layout->addWidget(medicineComboBox, 1, 0);

    // Stock display
    stockLabel = new QLabel("Stock: " + QString::number(medicines[selectedMedicineIndex].stock), this);
    layout->addWidget(stockLabel, 1, 1);

    // Dispense button
    QPushButton *dispenseButton = new QPushButton("Dispense Medicine", this);
    layout->addWidget(dispenseButton, 2, 0);

    // View stock button
    QPushButton *viewStockButton = new QPushButton("View Stock", this);
    layout->addWidget(viewStockButton, 2, 1);

    // Upload prescription button
    QPushButton *uploadPrescriptionButton = new QPushButton("Upload Prescription", this);
    layout->addWidget(uploadPrescriptionButton, 3, 0);

    // Consult doctor button
    QPushButton *consultDoctorButton = new QPushButton("Consult Doctor", this);
    layout->addWidget(consultDoctorButton, 3, 1);

    // Login section
    QLabel *loginLabel = new QLabel("Login", this);
    layout->addWidget(loginLabel, 4, 0);
    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Username");
    layout->addWidget(usernameInput, 5, 0);
    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordInput, 5, 1);
    
    QPushButton *loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton, 6, 0);
    
    QPushButton *signupButton = new QPushButton("Signup", this);
    layout->addWidget(signupButton, 6, 1);

    // Connect signals to slots
    connect(dispenseButton, &QPushButton::clicked, this, &MainWindow::onDispenseClicked);
    connect(viewStockButton, &QPushButton::clicked, this, &MainWindow::onViewStockClicked);
    connect(uploadPrescriptionButton, &QPushButton::clicked, this, &MainWindow::onUploadPrescriptionClicked);
    connect(consultDoctorButton, &QPushButton::clicked, this, &MainWindow::onConsultDoctorClicked);
    connect(medicineComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::onMedicineSelected);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(signupButton, &QPushButton::clicked, this, &MainWindow::onSignupClicked);

    setWindowTitle("Medicine Vending Machine");
    resize(400, 300);
}

MainWindow::~MainWindow() {
    // Destructor if needed for any cleanup
}

void MainWindow::onDispenseClicked() {
    dispenseMedicine(selectedMedicineIndex);
}

void MainWindow::onViewStockClicked() {
    showStock();
}

void MainWindow::onUploadPrescriptionClicked() {
    QMessageBox::information(this, "Upload Prescription", "Prescription uploaded successfully!");
}

void MainWindow::onConsultDoctorClicked() {
    QMessageBox::information(this, "Consult Doctor", "Connecting you to a doctor...");
}

void MainWindow::onMedicineSelected(int index) {
    selectedMedicineIndex = index;
    updateStockDisplay();
}

void MainWindow::updateStockDisplay() {
    stockLabel->setText("Stock: " + QString::number(medicines[selectedMedicineIndex].stock));
}

void MainWindow::dispenseMedicine(int index) {
    if (medicines[index].stock > 0) {
        medicines[index].stock--;
        updateStockDisplay();
        QMessageBox::information(this, "Dispense", medicines[index].name + " dispensed successfully!");
    } else {
        QMessageBox::warning(this, "Out of Stock", medicines[index].name + " is out of stock!");
    }
}

void MainWindow::showStock() {
    QString stockInfo = "Current stock:\n";
    for (int i = 0; i < 5; ++i) {
        stockInfo += medicines[i].name + ": " + QString::number(medicines[i].stock) + "\n";
    }
    QMessageBox::information(this, "Stock Information", stockInfo);
}

void MainWindow::onLoginClicked() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (users.contains(username) && users[username] == password) {
        QMessageBox::information(this, "Login", "Login successful!");
    } else {
        QMessageBox::warning(this, "Login", "Invalid username or password.");
    }
}

void MainWindow::onSignupClicked() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (users.contains(username)) {
        QMessageBox::warning(this, "Signup", "Username already exists. Please try logging in.");
    } else {
        users[username] = password;
        QMessageBox::information(this, "Signup", "Signup successful! You can now log in.");
    }
}
