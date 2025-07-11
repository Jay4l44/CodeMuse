#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Patient {
    int id;
    char name[100];
    int age;
    char condition[100];
    int severity;
} Patient;

typedef struct Doctor {
    int id;
    char name[100];
    char specialty[100];
    int isAvailable;
    struct Doctor* next;
} Doctor;

typedef struct Node {
    Patient data;
    struct Node* next;
} Node;

typedef struct StackNode {
    Patient data;
    struct StackNode* next;
} StackNode;

typedef struct RecordNode {
    Patient data;
    struct RecordNode* left;
    struct RecordNode* right;
} RecordNode;

Node* front = NULL;
Node* rear = NULL;
StackNode* emergencyTop = NULL;
Doctor* doctorHead = NULL;
RecordNode* recordRoot = NULL;

void enqueue(Patient p) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = p;
    temp->next = NULL;
    if (rear == NULL) {
        front = rear = temp;
    } else {
        rear->next = temp;
        rear = temp;
    }
}

Patient dequeue() {
    if (front == NULL) {
        printf("Queue is empty.\n");
        exit(1);
    }
    Node* temp = front;
    Patient p = temp->data;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
    return p;
}

void push(Patient p) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->data = p;
    temp->next = emergencyTop;
    emergencyTop = temp;
}

Patient pop() {
    if (emergencyTop == NULL) {
        printf("Stack is empty.\n");
        exit(1);
    }
    StackNode* temp = emergencyTop;
    Patient p = temp->data;
    emergencyTop = emergencyTop->next;
    free(temp);
    return p;
}

int isEmergencyEmpty() {
    return emergencyTop == NULL;
}

RecordNode* insertRecord(RecordNode* root, Patient p) {
    if (root == NULL) {
        RecordNode* temp = (RecordNode*)malloc(sizeof(RecordNode));
        temp->data = p;
        temp->left = temp->right = NULL;
        return temp;
    }
    if (p.id < root->data.id)
        root->left = insertRecord(root->left, p);
    else
        root->right = insertRecord(root->right, p);
    return root;
}

void inorder(RecordNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("ID: %d | Name: %s | Age: %d | Condition: %s | Severity: %d\n",
               root->data.id, root->data.name, root->data.age, root->data.condition, root->data.severity);
        inorder(root->right);
    }
}

RecordNode* searchRecord(RecordNode* root, int id) {
    if (root == NULL || root->data.id == id) return root;
    if (id < root->data.id)
        return searchRecord(root->left, id);
    else
        return searchRecord(root->right, id);
}

void addDoctor() {
    Doctor* newDoc = (Doctor*)malloc(sizeof(Doctor));
    printf("Enter Doctor ID: ");
    scanf("%d", &newDoc->id);
    printf("Enter Name: ");
    scanf(" %[^\n]", newDoc->name);
    printf("Enter Specialty: ");
    scanf(" %[^\n]", newDoc->specialty);
    newDoc->isAvailable = 1;
    newDoc->next = NULL;

    if (doctorHead == NULL) {
        doctorHead = newDoc;
    } else {
        Doctor* temp = doctorHead;
        while (temp->next) temp = temp->next;
        temp->next = newDoc;
    }
}

void displayDoctors() {
    Doctor* temp = doctorHead;
    while (temp) {
        printf("ID: %d | Name: %s | Specialty: %s | Available: %s\n",
               temp->id, temp->name, temp->specialty, temp->isAvailable ? "Yes" : "No");
        temp = temp->next;
    }
}

void removeDoctor() {
    int id;
    printf("Enter Doctor ID to remove: ");
    scanf("%d", &id);
    Doctor *temp = doctorHead, *prev = NULL;

    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) {
        printf("Doctor not registered.\n");
        return;
    }
    if (!prev) doctorHead = temp->next;
    else prev->next = temp->next;
    free(temp);
    printf("Doctor removed.\n");
}

Doctor* getAvailableDoctor() {
    Doctor* temp = doctorHead;
    while (temp) {
        if (temp->isAvailable) return temp;
        temp = temp->next;
    }
    return NULL;
}

void toggleDoctorAvailability() {
    int id;
    printf("Enter Doctor ID: ");
    scanf("%d", &id);
    Doctor* temp = doctorHead;
    while (temp) {
        if (temp->id == id) {
            temp->isAvailable = !temp->isAvailable;
            printf("Doctor Currently: %s\n", temp->isAvailable ? "Available" : "Unavailable");
            return;
        }
        temp = temp->next;
    }
    printf("Doctor not registered.\n");
}

void registerPatient() {
    Patient p;
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Condition: ");
    scanf(" %[^\n]", p.condition);
    printf("Enter Severity (From 1 to 10): ");
    scanf("%d", &p.severity);

    enqueue(p);
    if (p.severity > 7) {
        push(p);
    }
    printf("Patient registered.\n");
}

void assignPatient() {
    Doctor* doc = getAvailableDoctor();
    if (!doc) {
        printf("No available doctors right now.\n");
        return;
    }

    Patient p;
    if (!isEmergencyEmpty()) {
        p = pop();
    } else {
        if (front == NULL) {
            printf("No patients registered.\n");
            return;
        }
        p = dequeue();
    }

    doc->isAvailable = 0;
    printf("Assigning Patient %s to Doctor %s\n", p.name, doc->name);

    recordRoot = insertRecord(recordRoot, p);
    doc->isAvailable = 1;
}

//menu

int main() {
    int choice;
    do {
        printf("\n============== AAST Hospital ==============\n");
        printf("1. Register new patient\n");
        printf("2. Add new doctor\n");
        printf("3. Assign patient to doctor\n");
        printf("4. View all doctors\n");
        printf("5. Remove a doctor\n");
        printf("6. View all treated patients\n");
        printf("7. Search treated patient by ID\n");
        printf("8. Check doctor availability\n");
        printf("9. Insert treated patient\n");
        printf("10. Exit\n");
        printf("===========================================\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerPatient(); break;
            case 2: addDoctor(); break;
            case 3: assignPatient(); break;
            case 4: displayDoctors(); break;
            case 5: removeDoctor(); break;
            case 6: inorder(recordRoot); break;
            case 7: {
                int id;
                printf("Enter Patient ID: ");
                scanf("%d", &id);
                RecordNode* found = searchRecord(recordRoot, id);
                if (found) {
                    printf("Found: ID: %d | Name: %s | Condition: %s | Severity: %d\n",
                        found->data.id, found->data.name, found->data.condition, found->data.severity);
                } else {
                    printf("Patient not registered.\n");
                }
                break;
            }
            case 8: toggleDoctorAvailability(); break;
            case 9: {
                Patient p;
                printf("Enter Patient ID: ");
                scanf("%d", &p.id);
                printf("Enter Name: ");
                scanf(" %[^\n]", p.name);
                printf("Enter Age: ");
                scanf("%d", &p.age);
                printf("Enter Condition: ");
                scanf(" %[^\n]", p.condition);
                printf("Enter Severity (From 1 to 10): ");
                scanf("%d", &p.severity);
                recordRoot = insertRecord(recordRoot, p);
                printf("Record added.\n");
                break;
            }
            case 10: printf("Exiting... XD\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 10);

    return 0;
}
