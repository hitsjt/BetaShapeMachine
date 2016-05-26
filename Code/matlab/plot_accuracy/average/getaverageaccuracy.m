function  accuracy = getaverageaccuracy(file_name, file_name1,file_name2,file_name3)
a_1 = getaccuracy(file_name);
a_2 = getaccuracy(file_name1);
a_3 = getaccuracy(file_name2);
a_4 = getaccuracy(file_name3);
accuracy = (a_1+a_2+a_3+a_4)/4;
accuracy(24)
accuracy(48)
accuracy(72)
accuracy(96)
accuracy(120)