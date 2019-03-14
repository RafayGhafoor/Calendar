
int getMonth()
{
    int mon;
    cout << "Enter month number (1-12): ";
    while (cin >> mon)
    {
        if (isValidMonth(--mon))
            return mon;
        cout << "Invalid Month specified." << endl;
    }
    return mon;
}