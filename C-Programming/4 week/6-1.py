print("Enter your height")
feet=int(input("Feet: "))
inch=int(input("Inches: ")) 

cm=float(inch*2.54)+feet*(30.48) # 입력받은 inch와 feet값을 cm로 바꿔서 더해준다
board=float(cm*0.88) # 바꿔준 cm값을 0.88을 곱하여 board 길이를 구한다

print("Suggested board length: ", board, "cm")
