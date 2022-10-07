#include <iostream>
#include <string>
using namespace std;

class applicant
{
    string name;
    int age;
    string address;
    int monthly_salary;
    int home_loan;
    int personal_loan;
    int no_cheque_bounce;
    char own_house;
    char spouse_working;
    char dependent_parents;
    int company_tier;
    int yes, no;
    int liability;

public:
    void get_data();
    int calculate_liability();
    void display_score();
};

/**
 * requests the applicant's data required for processing.
 *
 * @returns None
 */
void applicant::get_data()
{
    cout << "\n\nName of applicant (Press | to terminate): " << endl;
    getline(cin, name, '|');

    cout << "\nAge : " << endl;
    cin >> age;

    cout << "\nAddress (Press | to terminate): " << endl;
    getline(cin, address, '|');

    cout << "\nMonthly Salary : " << endl;
    cin >> monthly_salary;

    cout << "\nTotal home loan EMI : " << endl;
    cin >> home_loan;

    cout << "\nTotal personal loan EMI : " << endl;
    cin >> personal_loan;

    cout << "\nNumber of cheque bounces in last 6 months : " << endl;
    cin >> no_cheque_bounce;

    cout << "\n\nOwn house? (Y or N) : " << endl;
    cin >> own_house;

    cout << "\nSpouse working? (Y or N) : " << endl;
    cin >> spouse_working;

    cout << "\nDependent parents? (Y or N) : " << endl;
    cin >> dependent_parents;

    cout << "\nCompany Tier (1,2 or 3) : " << endl;
    cin >> company_tier;
}

/**
 * Calculates the applicant's liability.
 *
 * @returns The applicant's liability.
 */
int applicant::calculate_liability()
{
    int score = 0;

    /*details of applicant age*/
    if (age > 22 && age <= 30)
    {
        score = score + 2;
    }
    else if (age > 30 && age <= 35)
    {
        score = score + 2;
    }
    else
    {
        score = score - 1;
    }

    liability = home_loan + personal_loan;

    score = liability <= monthly_salary / 4 ? score + 5 : score;
    score = (liability > monthly_salary / 4 && liability <= monthly_salary / 3) ? score + 3 : score;
    score = (liability > monthly_salary / 3 && liability <= monthly_salary / 2) ? score + 1 : score;
    score = liability > monthly_salary / 2 ? score - 1 : score;

    if (no_cheque_bounce == 0)
    {
        score = score + 1;
    }

    if (no_cheque_bounce == 1)
    {
        score = score - 1;
    }

    if (no_cheque_bounce > 1)
    {
        score = score - 2;
    }

    score = (personal_loan + home_loan) ? score - 1 : score + 1;
    score = own_house == 'Y' ? score + 1 : score;
    score = spouse_working == 'Y' ? score + 1 : score;
    score = dependent_parents == 'Y' ? score - 1 : score + 1;

    if (company_tier == 1)
    {
        score = score + 3;
    }

    if (company_tier == 2)
    {
        score = score + 2;
    }
    else
    {
        score = score + 1;
    }

    return (score);
}

void applicant::display_score()
{
    int score = calculate_liability();

    if (score > 9)
    {
        cout << "\nThe applicant " << name << " is at low risk.\ncredit score = " << score << "\nCredit can be given." << endl;
    }
    else
    {
        if (score > 5 && score <= 9)
        {
            cout << "\nThe applicant " << name << " is at average risk.\ncredit score = " << score << "\nCredit can be given with due precaution." << endl;
        }
        else
        {
            cout << "\nThe applicant " << name << " is at high risk.\ncredit score = " << score << "\nCredit can not  be given" << endl;
        }
    }
}

int user_menu()
{
    int choice;
    cout << "\n\n\t\t\t\t\t\t\t   Credit Calculator" << endl;
    cout << "\t\t\t\t\t\t\t   *****************" << endl;
    cout << "\n1 - Enter loan applicant details." << endl;
    cout << "2 - Display credit score." << endl;
    cout << "3 - Exit." << endl;
    cout << "\nSelect an option." << endl;
    cin >> choice;

    return (choice);
}

int main()
{
    applicant app;
    char flag = 'f';
    int menu_option;

    while (menu_option > 0)
    {
        menu_option = user_menu();

        switch (menu_option)
        {
        case 1:
            app.get_data();
            flag = 't';

            break;

        case 2:
            if (flag == 'f')
            {
                cout << "Loan applicant details not yet entered! Input the details..." << endl;
                app.get_data();
                app.display_score();
            }
            else
            {
                app.display_score();
            }

            break;

        case 3:
            cout << "Bye - Bye!" << endl;
            exit(0);

        default:
            cout << "Invalid Input. Please try again" << endl
                 << endl;
        }
    }

    return (0);
}