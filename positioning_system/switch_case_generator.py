l = []
def switch(i, string, offset):
    o = "LOW"
    for x in range(i * 2 + 1):
##        print(round(256 * x / i / 2))
        l.append((round(256 * x / i / 2) + offset, string, o))
        if o == "LOW":
            o = "HIGH"
        else:
            o = "LOW"

            
##print("  switch (frequency_selector) {")
##for e in (3,4,5):
##    print("    case {}: \n      switch (frequency_counter) {".format(e - 3))
##    l = []
##    switch(3, "low")
##    for e in l:
##        print("      case {}:\n        digitalWrite({}_frequency_pin, {});\n      break;".format(*e))
##    print("      };\n      break;")
    
    
switch(3, "low", 0)
switch(3, "low", 256)
switch(4, "middle", 512)
switch(4, "middle", 768)
switch(5, "high", 1024)
switch(5, "high", 1280)
l.sort()
print("  switch (frequency_counter) {")
li = iter(l)
for i, e in enumerate(li):
    if not i > 1 or not l[i - 1][0] == e[0]:
        print("    case {}:".format(e[0]))
    if not i < len(l) - 1 or not l[i + 1] == e:
        print("      digitalWrite({}_frequency_pin, {});".format(*e[1:]))
    if not i < len(l) - 1 or not l[i + 1][0] == e[0]:
        print("      break;")
print("  }")
