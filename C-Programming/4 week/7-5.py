def convert_to_celsius(f):
    tc=float((5/9)*(float(f)-32))
    return tc

def convert_to_kelvin(f):
    tk=float(convert_to_celsius(f))+273.15
    return tk

def convert_temp():
    f=float(input("Enter a temperature in Fahrenheit: "))
    print("")
    print("The temperature in Fahrenheit is: ", f)
    print("The temperature in Celsius is: ", convert_to_celsius(f))
    print("The temperature in Kelvin is: ", convert_to_kelvin(f))
