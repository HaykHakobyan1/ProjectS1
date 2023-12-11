#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADMIN_PASSWORD "admin123"  // Change this to your desired password

static int p = 0;

struct Bus {
    char busn[6], driver[20], arrival[6], depart[6], from[20], to[20], seat[8][4][20];
};


void analyze(struct Bus *buses) {
    int totalSeats = 0;
    int reservedSeats = 0;
    int seats[32] = {0}; // Array to store the count of each seat being reserved
    int destinations[10] = {0}; // Array to store the count of each destination

    // Iterate through buses
    for (int n = 0; n < p; n++) {
        // Iterate through rows and columns of seats
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                totalSeats++;
                if (strcmp(buses[n].seat[i][j], "Empty") != 0) {
                    reservedSeats++;
                    int seatNumber = i * 4 + j + 1;
                    seats[seatNumber - 1]++; // Increment the count of the reserved seat
                }
            }
        }
        // Increment the count of each destination
        int destIndex = 0;
        while (destIndex < 10 && destinations[destIndex] != 0 && strcmp(buses[n].to, buses[destIndex].to) != 0) {
            destIndex++;
        }
        if (destIndex < 10) {
            destinations[destIndex]++;
        }
    }

    // Find the most frequent seat
    int maxSeat = 0;
    for (int i = 1; i < 32; i++) {
        if (seats[i] > seats[maxSeat]) {
            maxSeat = i;
        }
    }

    // Find the most popular destination
    int maxDest = 0;
    for (int i = 1; i < 10; i++) {
        if (destinations[i] > destinations[maxDest]) {
            maxDest = i;
        }
    }

    printf("\nTotal seats: %d\nReserved seats: %d\n", totalSeats, reservedSeats);
    printf("Most frequent seat: %d\nMost popular destination: %s\n", maxSeat + 1, buses[maxDest].to);
}


void vline(char ch) {
    for (int i = 80; i > 0; i--)
        printf("%c", ch);
}

int getValidInteger() {
    int num;
    while (1) {
        if (scanf("%d", &num) == 1) {
            break;
        } else {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
        }
    }
    return num;
}

void install(struct Bus *buses) {
    printf("Enter bus no: ");
    scanf("%s", buses[p].busn);

    printf("\nEnter Driver's name: ");
    scanf("%s", buses[p].driver);

    printf("\nArrival time (HH:MM): ");
    scanf("%s", buses[p].arrival);

    printf("\nDeparture time (HH:MM): ");
    scanf("%s", buses[p].depart);

    printf("\nFrom: \t\t\t");
    scanf("%s", buses[p].from);

    printf("\nTo: \t\t\t");
    scanf("%s", buses[p].to);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            strcpy(buses[p].seat[i][j], "Empty");
        }
    }

    p++;
}

void allotment(struct Bus *buses) {
    int seat;
    char number[5];

    printf("Bus no: ");
    scanf("%s", number);

    int n;
    for (n = 0; n <= p; n++) {
        if (strcmp(buses[n].busn, number) == 0)
            break;
    }

    while (n <= p) {
        printf("\nSeat Number: ");
        seat = getValidInteger();

        if (seat < 1 || seat > 32) {
            printf("\nInvalid seat number. There are only 32 seats available in this bus.\n");
        } else {
            int row = (seat - 1) / 4;
            int col = (seat - 1) % 4;
            if (strcmp(buses[n].seat[row][col], "Empty") == 0) {
                printf("Enter passenger's name: ");
                scanf("%s", buses[n].seat[row][col]);
                break;
            } else {
                printf("The seat no. is already reserved.\n");
            }
        }
    }

    if (n > p) {
        printf("Enter correct bus no.\n");
    }
}

void show(struct Bus *buses) {
    int n;
    char number[5];

    printf("Enter bus no: ");
    scanf("%s", number);

    for (n = 0; n <= p; n++) {
        if (strcmp(buses[n].busn, number) == 0)
            break;
    }

    while (n <= p) {
        vline('*');
        printf("Bus no: \t%s\nDriver: \t%s\t\tArrival time: \t%s\tDeparture time: %s\nFrom: \t\t%s\t\tTo: \t\t%s\n",
               buses[n].busn, buses[n].driver, buses[n].arrival, buses[n].depart, buses[n].from, buses[n].to);
        vline('*');

        int a = 1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 4; j++) {
                a++;
                if (strcmp(buses[n].seat[i][j], "Empty") != 0)
                    printf("\nThe seat no %d is reserved for %s.", (a - 1), buses[n].seat[i][j]);
            }
        }

        break;
    }

    if (n > p) {
        printf("Enter correct bus no: ");
    }
}

void position(struct Bus *buses, int l) {
    int s = 0, q = 0;

    for (int i = 0; i < 8; i++) {
        printf("\n");
        for (int j = 0; j < 4; j++) {
            s++;
            if (strcmp(buses[l].seat[i][j], "Empty") == 0) {
                printf("%d. %-10s", s, buses[l].seat[i][j]);
                q++;
            } else {
                printf("%d. %-10s", s, buses[l].seat[i][j]);
            }
        }
    }

    printf("\n\nThere are %d seats empty in Bus No: %s", q, buses[l].busn);
}

void avail(struct Bus *buses) {
    for (int n = 0; n < p; n++) {
        vline('*');
        printf("Bus no: \t%s\nDriver: \t%s\t\tArrival time: \t%s\tDeparture Time: %s\nFrom: \t\t%s\t\tTo: \t\t%s\n",
               buses[n].busn, buses[n].driver, buses[n].arrival, buses[n].depart, buses[n].from, buses[n].to);
        vline('*');
        vline('_');
    }
}

int authenticateAdmin() {
    char password[20];
    printf("Enter admin password: ");
    scanf("%s", password);

    if (strcmp(password, ADMIN_PASSWORD) == 0) {
        return 1;  // Authentication successful
    } else {
        printf("Incorrect password. Access denied.\n");
        return 0;  // Authentication failed
    }
}

void editReservation(struct Bus *buses) {
    if (authenticateAdmin()) {
        int n;
        char number[5];

        printf("Enter bus no: ");
        scanf("%s", number);

        for (n = 0; n <= p; n++) {
            if (strcmp(buses[n].busn, number) == 0)
                break;
        }

        while (n <= p) {
            vline('*');
            printf("Bus no: \t%s\nDriver: \t%s\t\tArrival time: \t%s\tDeparture time: %s\nFrom: \t\t%s\t\tTo: \t\t%s\n",
                buses[n].busn, buses[n].driver, buses[n].arrival, buses[n].depart, buses[n].from, buses[n].to);
            vline('*');

            int seat;
            printf("\nEnter Seat Number to edit/cancel reservation: ");
            seat = getValidInteger();

            if (seat < 1 || seat > 32) {
                printf("\nInvalid seat number. There are only 32 seats available in this bus.\n");
            } else {
                int row = (seat - 1) / 4;
                int col = (seat - 1) % 4;
                if (strcmp(buses[n].seat[row][col], "Empty") == 0) {
                    printf("The seat no. is not reserved.\n");
                } else {
                    printf("Current reservation: Seat no %d is reserved for %s.\n", seat, buses[n].seat[row][col]);
                    printf("Do you want to edit (1) or cancel (2) this reservation? Enter 0 to exit: ");
                    int choice = getValidInteger();

                    if (choice == 1) {
                        printf("Enter new passenger's name: ");
                        scanf("%s", buses[n].seat[row][col]);
                        printf("Reservation edited successfully.\n");
                    } else if (choice == 2) {
                        strcpy(buses[n].seat[row][col], "Empty");
                        printf("Reservation canceled successfully.\n");
                    } else {
                        printf("Invalid choice. Reservation remains unchanged.\n");
                    }
                }
            }

            break;
        }

        if (n > p) {
            printf("Enter correct bus no: ");
        }
    }
}

int main() {
    struct Bus buses[10];
    int w;

    while (1) {
        printf("\n\n\n\n\n");
        printf("\t\t\t1.Install\n\t\t\t"
               "2.Reservation\n\t\t\t"
               "3.Show\n\t\t\t"
               "4.Buses Available\n\t\t\t"
               "5.Edit Reservation (Admin)\n\t\t\t"
               "6.Analyze\n\t\t\t"
               "7.Exit");
        printf("\n\t\t\tEnter your choice:-> ");
        w = getValidInteger();

        switch (w) {
            case 1:
                install(buses);
                break;
            case 2:
                allotment(buses);
                break;
            case 3:
                show(buses);
                break;
            case 4:
                avail(buses);
                break;
            case 5:
                editReservation(buses);
                break;
             case 6:
                analyze(buses);
                break;

            case 7:
                exit(0);
        }
    }

    return 0;
}
