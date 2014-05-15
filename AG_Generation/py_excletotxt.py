import xlrd     
#read excle need lib xlrd

data=xlrd.open_workbook('BAGRA.xls')
#open excle

table=data.sheets()[0]
#select sheet

files=open('BAGRA.txt','w')
#open txt

for i1 in range(table.nrows):
    rows=table.row_values(i1)
    for i2 in range(0,6):
        str1=rows[i2]
        files.write(str(str1))
        files.write('\t')
    files.write(',')

files.close()

    
    
