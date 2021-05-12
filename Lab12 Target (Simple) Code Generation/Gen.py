import time
def findoperation(stmt, op, label):
    if(op == ">"):
        cmp = "BGT "+label
        print("ARM STATEMENT: ", cmp)
        time.sleep(0.02)
        stmt.append(cmp)
    elif(op == "<"):
        cmp = "BLT "+label
        print("ARM STATEMENT: ", cmp)
        time.sleep(0.02)
        stmt.append(cmp)
    elif(op == ">="):
        cmp = "BGE "+label
        print("ARM STATEMENT: ", cmp)
        time.sleep(0.02)
        stmt.append(cmp)
    elif(op == "<="):
        cmp = "BLE "+label
        print("ARM STATEMENT: ", cmp)
        time.sleep(0.02)
        stmt.append(cmp)
    elif(op == "=="):
        cmp = "BEQ "+label
        print("ARM STATEMENT: ", cmp)
        time.sleep(0.02)
        stmt.append(cmp)
    elif(op == "!="):
        cmp = "BNE "+label
        print("ARM STATEMENT: ", cmp)
        time.sleep(0.02)
        stmt.append(cmp)
    return stmt

def loadconstant(stmt, regval, value):
    lstmt = "MOV "+"R"+str(regval)+"," + "#" + value
    stmt.append(lstmt)
    print("ARM STATEMENT: ", lstmt)
    time.sleep(0.02)
    r1 = regval
    regval = (regval + 1)%13
    return stmt, regval, r1


def loadvariable(stmt, regval, value, isarr, offset=None):
    if(isarr == 0):
        st1 = "MOV "+"R" + str(regval) + ","+"="+str(value)
        r1 = regval
        regval = (regval + 1)%13
                
        print("ARM STATEMENT: ", st1)
        time.sleep(0.02)
        stmt.append(st1)
    
        st2 = "MOV "+"R" + str(regval) +","+ "[R" + str(r1) + "]"
        stmt.append(st2)
        print("ARM STATEMENT: ", st2)
        time.sleep(0.02)
        r2 = regval
        regval = (regval + 1)%13
        return stmt, regval, r1, r2
    else:
        st1 = "MOV "+"R" + str(regval) + ","+"="+str(value)
        r1 = regval
        regval = (regval + 1)%13
        
        print("ARM STATEMENT: ", st1)
        time.sleep(0.02)
        stmt.append(st1)
        if(not offset.isdigit()):
            st2 = "MOV "+"R" + str(regval) +","+ "[R" + str(r1) + "," + str(offset)+"]"
        else:
            st2 = "MOV "+"R" + str(regval) +","+ "[R" + str(r1) + "," + " #" + str(offset)+"]"
        stmt.append(st2)
        print("ARM STATEMENT: ", st2)
        time.sleep(0.02)
        r2 = regval
        regval = (regval + 1)%13
        return stmt, regval, r1, r2
def binaryoperation(stmt, lhs, arg1, op, arg2):
    if(op == "+"):
        st = "ADD "+"R"+str(lhs)+","+"R"+str(arg1)+",R"+str(arg2)
        print("ARM STATEMENT: ", st)
        time.sleep(0.02)
        stmt.append(st)
        
    elif(op == "-"):
        st = "SUBS "+"R"+str(lhs)+","+"R"+str(arg1)+",R"+str(arg2)
        print("ARM STATEMENT: ", st)
        time.sleep(0.02)
        stmt.append(st)        
        
    elif(op == "*"):
        st = "MUL "+"R"+str(lhs)+","+"R"+str(arg1)+",R"+str(arg2)
        print("ARM STATEMENT: ", st)
        time.sleep(0.02)
        stmt.append(st)        
        
    elif(op == "/"):
        st = "SDIV "+"R"+str(lhs)+","+"R"+str(arg1)+",R"+str(arg2)
        print("ARM STATEMENT: ", st)
        time.sleep(0.02)
        stmt.append(st)   
    return stmt
offset = 0    
def genAssembly(lines, file):
    vardec = []
    stmt = []
    varlist = []
    regval = 0
    for i in lines:
        i = i.strip("\n")
        
        if(len(i.split()) == 2):
            if(i.split()[0] == "GOTO"):
                st = "B " + i.split()[1]
                print("ARM STATEMENT: ", st)
                time.sleep(0.02)
                stmt.append(st)
            else:
                st = i
                print("ARM STATEMENT: ", st)
                time.sleep(0.02)
                stmt.append(st)
        if(len(i.split()) == 5):
            lhs, ass, arg1, op, arg2 = i.split()
            if(lhs[0] == '*' and arg1[0] == '*'):
                if(arg2.isdigit()):
                    offset = arg2
                else:
                    stmt, regval, r1,r2 = loadvariable(stmt, regval, arg2, 0)
                    offset = "R"+str(r2)
                
            elif(arg1.isdigit() and arg2.isdigit()):
                
                stmt, regval, r1 = loadconstant(stmt, regval, arg1)
                stmt, regval, r2 = loadconstant(stmt, regval, arg2)
                if(lhs[0] == '*'):
                    stmt, regval, r3, r4 = loadvariable(stmt, regval, lhs[1:], 1, offset)
                else:
                    stmt, regval, r3, r4 = loadvariable(stmt, regval, lhs,0)
                stmt = binaryoperation(stmt, r4, r1, op, r2)
                if(lhs[0] == '*'):
                    st = "STR R"+str(r4) + ", [R" + str(r3) + ", #", str(offset)+"]"
                else:
                    st = "STR R"+str(r4) + ", [R" + str(r3) + "]"
                print("ARM STATEMENT: ", st)
                time.sleep(0.02)
                stmt.append(st)
                
            elif(arg1.isdigit()):
                stmt, regval, r1 = loadconstant(stmt, regval, arg1)
                if(arg2[0] == '*'):
                    stmt, regval, r2, r3 = loadvariable(stmt, regval, arg2[1:], 1, offset)
                else:
                    stmt, regval, r2, r3 = loadvariable(stmt, regval, arg2, 0)
                if(lhs[0] == '*'):
                    stmt, regval, r4, r5 = loadvariable(stmt, regval, lhs[1:], 1, offset)
                else:
                    stmt, regval, r4, r5 = loadvariable(stmt, regval, lhs, 0)
                stmt = binaryoperation(stmt, r5, r1, op, r3)
                if(lhs[0] == '*'):
                    st = "STR R"+str(r5) + ", [R" + str(r4) + ", #"+str(offset)+"]"
                else:
                    st = "STR R"+str(r5) + ", [R" + str(r4) + "]"
                print("ARM STATEMENT: ", st)
                time.sleep(0.02)
                stmt.append(st)
                #STR Op
            elif(arg2.isdigit()):
                if(arg1[0] == '*'):
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, arg1[1:], 1, offset)
                else:
                    stmt, regval, r1,r2 = loadvariable(stmt, regval, arg1, 0)
                stmt, regval, r3 = loadconstant(stmt, regval, arg2)
                if(lhs[0] == '*'):
                    stmt, regval, r4, r5 = loadvariable(stmt, regval, lhs[1:], 1, offset)
                else:
                    stmt, regval, r4, r5 = loadvariable(stmt, regval, lhs,0)
                stmt = binaryoperation(stmt, r5, r2, op, r3)
                if(lhs[0] == '*'):
                    st = "STR R"+str(r5) + ", [R" + str(r4) + ", #"+str(offset)+"]"
                else:
                    st = "STR R"+str(r5) + ", [R" + str(r4) + "]"
                print("ARM STATEMENT: ", st)
                time.sleep(0.02)
                stmt.append(st)                
            else:
                if(arg1[0] == '*'):
                    stmt, regval, r1,r2 = loadvariable(stmt, regval, arg1[1:], 1, offset)
                else:
                    stmt, regval, r1,r2 = loadvariable(stmt, regval, arg1, 0)
                if(arg2[0] == '*'):
                    stmt, regval, r3,r4 = loadvariable(stmt, regval, arg2[1:], 1, offset)
                else:
                    stmt, regval, r3,r4 = loadvariable(stmt, regval, arg2)
                if(lhs[0] == '*'):
                    stmt, regval, r5,r6 = loadvariable(stmt, regval, lhs[1:], 1, offset)
                else:
                    stmt, regval, r5,r6 = loadvariable(stmt, regval, lhs, 0)
                stmt = binaryoperation(stmt, r6, r2, op, r4)
                if(lhs[0] == '*'):
                    st = "STR R"+str(r6) + ", [R" + str(r5) + ", #"+str(offset)+"]"
                else:
                    st = "STR R"+str(r6) + ", [R" + str(r5) + "]"
                print("ARM STATEMENT: ", st)
                time.sleep(0.02)
                stmt.append(st)
        if(len(i.split())==4 and i.split()[0]=="ARR"):
            variable = i.split()[1]
            value = i.split()[3].split(",")
            if(variable not in varlist):
                out = ""
                out = out + variable + ":" + " .WORD "
                vals = ""
                for x in value:
                    vals = vals + x + " "
                out = out + vals
                print("ARM DECLARATION :", out)
                time.sleep(0.02)
                vardec.append(out)
                varlist.append(variable)
                
        if(len(i.split()) == 4 and i.split()[0]!="ARR"):
            
            condition = i.split()[1]
            label = i.split()[3]
            flag = 0
            lhs = ""
            rhs = ""
            operator = [">", "<", ">=", "<=", "=", "!"]
            op = ""
            for j in condition:
                if(j in operator):
                    op = op + j
                    flag = 1
                    continue
                if(j == "="):
                    op = op + j
                    continue
                if(flag == 0):
                    lhs += j
                else:
                    rhs+=j
            
            if(rhs.isdigit() and lhs.isdigit()):
                stmt, regval, r1 = loadconstant(stmt, regval, lhs)
                stmt, regval, r2 = loadconstant(stmt, regval, rhs)
                cmp = "CMP R"+str(r1)+", "+"R"+str(r2)
                print("ARM STATEMENT: ", cmp)
                time.sleep(0.02)
                stmt.append(cmp)
                stmt = findoperation(stmt, op, label)
                
            elif(lhs.isdigit()):
                stmt, regval, r1 = loadconstant(stmt, regval, lhs)
                if(rhs[0] == '*'):
                    stmt, regval, r2, r3 = loadvariable(stmt, regval, rhs[1:], 1, offset)
                else:
                    stmt, regval, r2, r3 = loadvariable(stmt, regval, rhs, 0)
                
                st4 = "CMP " + "R"+str(r1) + "," + "R" + str(r3)
                print("ARM STATEMENT: ", st4)
                time.sleep(0.02)
                stmt.append(st4)
                stmt = findoperation(stmt, op, label)
            elif(rhs.isdigit()):
                if(lhs[0] == '*'):
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, lhs[1:], 1, offset)
                else:
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, lhs, 0)
                stmt, regval, r3 = loadconstant(stmt, regval, rhs)
                st4 = "CMP " + "R"+str(r2) + "," + "R" + str(r3)
                print("ARM STATEMENT: ", st4)
                time.sleep(0.02)
                stmt.append(st4)
                stmt = findoperation(stmt, op, label)
            else:
                if(lhs[0] == '*'):
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, lhs[1:], 1, offset)
                else:
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, lhs, 0)
                if(rhs[0] == '*'):
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, lhs[1:], 1, offset)
                else:
                    stmt, regval, r3, r4 = loadvariable(stmt, regval, rhs, 0)
                
                st4 = "CMP " + "R"+str(r2) + "," + "R" + str(r4)
                print("ARM STATEMENT: ", st4)
                time.sleep(0.02)
                stmt.append(st4)
                stmt = findoperation(stmt, op, label)
                    
                
            
        if(len(i.split()) == 3):
            variable = i.split()[0]
            value = i.split()[2]
            variable = str(variable)
            if variable not in varlist:
                out = ""
                out = out + variable + ":" + " .WORD " + str(value)
                print("ARM DECLARATION :", out)
                time.sleep(0.02)
                vardec.append(out)
                varlist.append(variable)
            else:
                if(variable[0] == '*'):
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, variable[1:], 1, offset)
                else:
                    stmt, regval, r1, r2 = loadvariable(stmt, regval, variable, 0)
                stmt, regval, r3 = loadconstant(stmt, regval, value)
                if(variable[0] == '*'):
                    st = "STR R"+str(r3)+", [R" + str(r1) + ", #"+str(offset)+"]"
                else:
                    st = "STR R"+str(r3)+", [R" + str(r1) + "]"
                print("ARM STATEMENT: ", st)
                time.sleep(0.02)
                stmt.append(st)
    return vardec, stmt
                
                
            
def writeassembly(stmt, vardec, File):
    File.write(".text\n")
    for i in stmt:
        time.sleep(0.001)
        File.write("%s\n"%(i))
    File.write("SWI 0x011\n")
    File.write(".DATA\n")
    for i in vardec:
        
        time.sleep(0.01)
        File.write("%s\n"%(i))
    
    print("Written to File")

fin = open("input.txt", "r")
fout = open("output.s", "w")

lines = fin.readlines()
print("Generating Assembly ... ")
vardec, stmt = genAssembly(lines, fout)
print("Assembly Code Generated")
print("Writing to File")
print("---------------")
writeassembly(stmt, vardec, fout)
print("---------------")
print("Compilation Succesful")
fin.close()
fout.close()

fin.close()
fout.close()