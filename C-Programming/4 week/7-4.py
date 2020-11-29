def calc_new_height():
    width=float(input("Enter the current width: "))
    height=float(input("Enter the current height: "))
    desired_width=float(input("Enter the desired width: "))

    ratio=370/800
    desired_height=height*ratio

    print("The corresponding height is: ", desired_height)
    return desired_height
