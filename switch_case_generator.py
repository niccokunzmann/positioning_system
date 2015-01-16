l = []
def switch(i, string):
    o = "LOW"
    for x in range(i * 2):
        print(round(256 * x / i / 2))
        l.append((round(256 * x / i / 2), string, o))
        if o == "LOW":
            o = "HIGH"
        else:
            o = "LOW"

            

switch(3, "low")
switch(4, "middle")
switch(5, "high")
l.sort()
for e in l:
    print("    case {}:\n      digitalWrite({}_frequency_pin, {});\n      break;".format(*e))
