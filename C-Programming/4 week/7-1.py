def get_days(hours,minutes,seconds):
    minutes=float(minutes)+float(seconds)/60
    hours=float(hours)+float(minutes)/60
    days=float(hours)/24
    return float(days);

def convert_to_days():
    hours=input("Enter number of hours: ")
    minutes=input("Enter numberof minutes: ")
    seconds=input("Enter number of seconds: ")
    days=get_days(hours,minutes,seconds)
    print("The number of days is: ", round(days,4))
