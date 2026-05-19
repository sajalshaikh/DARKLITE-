#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <ctime>
#include <limits>

using namespace std;

void darkliteASCII() {
    cout << "\n";
    cout << "██████╗  █████╗ ██████╗ ██╗  ██╗██╗     ██╗████████╗███████╗\n";
    cout << "██╔══██╗██╔══██╗██╔══██╗██║ ██╔╝██║     ██║╚══██╔══╝██╔════╝\n";
    cout << "██║  ██║███████║██████╔╝█████╔╝ ██║     ██║   ██║   █████╗  \n";
    cout << "██║  ██║██╔══██║██╔══██╗██╔═██╗ ██║     ██║   ██║   ██╔══╝  \n";
    cout << "██████╔╝██║  ██║██║  ██║██║  ██╗███████╗██║   ██║   ███████╗\n";
    cout << "╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝   ╚═╝   ╚══════╝\n";
    cout << "═══════════════════════════════════════════════════════\n";
    cout << "   DARKLITE – Lightweight Security CLI Toolkit\n";
    cout << "   Authors: Sajal Sheikh\n";
    cout << "═══════════════════════════════════════════════════════\n";
}

struct Alert {
    string type;
    string message;
};

const int MAX_ALERTS = 50;
Alert alerts[MAX_ALERTS];
int alertIndex = 0;
int passwordCount = 0, bruteForceAlerts = 0, phishingAlerts = 0, portScanAlerts = 0, firewallAlerts = 0;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    string pause;
    getline(cin, pause);
}

void menu() {
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║            DARKLITE MAIN MENU          ║\n";
    cout << "╠════════════════════════════════════════╣\n";
    cout << "║ [1] Password Generator                 ║\n";
    cout << "║ [2] Brute Force Detection              ║\n";
    cout << "║ [3] Phishing URL Detector              ║\n";
    cout << "║ [4] Port Scan Simulator                ║\n";
    cout << "║ [5] Firewall Rule Checker              ║\n";
    cout << "║ [6] View Alerts & Summary              ║\n";
    cout << "║ [7] Exit                               ║\n";
    cout << "╚════════════════════════════════════════╝\n";
    cout << "Enter choice: ";
}

void passwordGenerator() {
    string charset = "", password;
    int length;
    bool up, low, dig, sym;

    cout << "\nPassword length (8–32): ";
    while (!(cin >> length) || length < 8 || length > 32) {
        cout << "Invalid! Try again: ";
        clearInput();
    }

    cout << "Include uppercase (1/0): "; cin >> up;
    cout << "Include lowercase (1/0): "; cin >> low;
    cout << "Include digits (1/0): "; cin >> dig;
    cout << "Include symbols (1/0): "; cin >> sym;

    if (up) charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (low) charset += "abcdefghijklmnopqrstuvwxyz";
    if (dig) charset += "0123456789";
    if (sym) charset += "!@#$%^&*";

    if (charset.empty()) {
        cout << "No character set selected!\n";
        clearInput();
        return;
    }

    for (int i = 0; i < length; i++)
        password += charset[rand() % charset.length()];

    cout << "Generated Password: " << password << "\n";

    alerts[alertIndex++] = { "Password Generator", password };
    passwordCount++;

    ofstream fout("passwords.txt", ios::app);
    fout << password << endl;
    fout.close();
    clearInput();
}

void bruteForceDetection() {
    string correct = "admin123", input;
    int attempts = 0;

    cout << "\nEnter password (3 attempts allowed)\n";
    while (attempts < 3) {
        cout << "Attempt " << attempts + 1 << ": ";
        cin >> input;

        if (input == correct) {
            cout << "Login successful!\n";
            clearInput();
            return;
        }
        attempts++;
        cout << "Wrong password!\n";
    }

    cout << "Brute-force detected!\n";
    alerts[alertIndex++] = { "Brute Force", "Multiple failed attempts" };
    bruteForceAlerts++;

    ofstream fout("brute_force_results.txt", ios::app);
    fout << "Brute-force detected: 3 failed attempts" << endl;
    fout.close();
    clearInput();
}

void phishingDetector() {
    string url;
    cout << "Enter URL: ";
    clearInput();
    getline(cin, url);

    string keywords[] = { "login", "verify", "secure", "bank" };
    bool suspicious = false;

    for (string k : keywords)
        if (url.find(k) != string::npos)
            suspicious = true;

    if (suspicious) {
        cout << "Phishing detected!\n";
        alerts[alertIndex++] = { "Phishing", url };
        phishingAlerts++;

        ofstream fout("phishing_results.txt", ios::app);
        fout << url << endl;
        fout.close();
    }
    else {

        cout << "URL appears safe.\n";
    }
}

void portScanner() {
    int count;
    cout << "Number of ports to scan: ";
    cin >> count;

    if (count >= 5) {
        cout << "Aggressive scanning detected!\n";
        alerts[alertIndex++] = { "Port Scan", "Multiple ports scanned" };
        portScanAlerts++;

        ofstream fout("port_scan_results.txt", ios::app);
        fout << "Multiple ports scanned: " << count << " ports" << endl;
        fout.close();
    }
    else {
        cout << "Normal port scan completed.\n";
    }

    clearInput();
}

void firewallChecker() {
    string input;
    cout << "Enter network action: ";
    clearInput();
    getline(cin, input);

    if (input.find("block") != string::npos || input.find("malware") != string::npos) {
        cout << "[BLOCKED] Firewall rule triggered\n";
        alerts[alertIndex++] = { "Firewall", input };
        firewallAlerts++;

        ofstream fout("firewall_results.txt", ios::app);
        fout << "[BLOCKED] " << input << endl;
        fout.close();
    }
    else {
        cout << "[ALLOWED] Traffic permitted\n";

        ofstream fout("firewall_results.txt", ios::app);
        fout << "[ALLOWED] " << input << endl;
        fout.close();
    }
}

void viewSummary() {
    cout << "\n========== SESSION SUMMARY ==========\n";
    cout << "Passwords Generated   : " << passwordCount << "\n";
    cout << "Brute Force Alerts    : " << bruteForceAlerts << "\n";
    cout << "Phishing Alerts       : " << phishingAlerts << "\n";
    cout << "Port Scan Alerts      : " << portScanAlerts << "\n";
    cout << "Firewall Rule Checker : " << firewallAlerts << "\n";
    cout << "Total Logs            : " << alertIndex << "\n";
    cout << "====================================\n";
}

int main() {
    srand(time(0));
    darkliteASCII();

    int choice;
    do {
        menu();
        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "Invalid input! Try again: ";
            clearInput();
        }

        switch (choice) {
        case 1: passwordGenerator(); break;
        case 2: bruteForceDetection(); break;
        case 3: phishingDetector(); break;
        case 4: portScanner(); break;
        case 5: firewallChecker(); break;
        case 6: viewSummary(); break;
        case 7: cout << "\nExiting DarkLite...\n"; break;
        }

        if (choice != 7) {
            waitForEnter();
        }

    } while (choice != 7);

    return 0;
}
