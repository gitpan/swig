use list;
package list;

$Users = new_List();
 
open(FILE,"/etc/passwd");
while (<FILE>) {
    @fields = split(":");
    $u = new_User($fields[4],$fields[2],$fields[5]);
    List_append($Users,$u);
}
close FILE;

for ($i = 0; $i < List_len($Users); $i++) {
    print User_str(ptrcast(List_get($Users,$i),"User *")),"\n";
}
