find . -name "*.c"  > cscope.files
find . -name "*.cpp"  >> cscope.files
find . -name "*.cc"  >> cscope.files
find . -name "*.java" >> cscope.files
cscope -bq 
