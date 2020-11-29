cent=float(input("Enter the cost per kilowatt-hour in cents: "))
per_year=input("Enter the number of kilowatt-hours used per year: ")

cost=float(cent)*float(per_year)/100

print("The annual cost will be: cost", cost)
print("The cost over 10 years will be", cost*10)
