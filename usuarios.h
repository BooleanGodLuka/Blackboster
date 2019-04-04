#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

void guardaradmin(admin ad){

FILE *p=fopen("admins.dat","ab");
if (p==NULL){
    cout << "error en el archivo" << endl;
    exit(-1);
}

fwrite(&ad,sizeof(admin),1,p);
fclose(p);

}

void guardarcliente(cliente cl){
FILE *p=fopen("clientes.dat","ab");
if (p==NULL){
    cout << "error en el archivo" << endl;
    exit(-1);
}

fwrite(&cl,sizeof(cliente),1,p);
fclose(p);

}

void sumar_cliente(char *us){
FILE *p=fopen("admins.dat","rb+");
if (p==NULL) exit(-1);
admin ad;
int b;

while (fread(&ad,sizeof(admin),1,p)==1){
    if (strcmp(ad.getnombre(),us)==0){
    ad.setcantclientes(ad.getcantclientes()+1);
    b=ftell(p);
    fseek(p,b-sizeof(admin),0);
    fwrite(&ad,sizeof (admin),1,p);
    fclose(p);
    }
}
}

void nuevoadmin() {
system("cls");
admin ad;

ad.pedir_admin();

while(validar_exist(ad,"admins.dat")){
    cout << "Usuario ya existente , pruebe de nuevo" << endl;
    ad.pedir_admin();
}

guardaradmin(ad);

}

void listar_admins(){
system("cls");
FILE *p=fopen("admins.dat","rb");
if (p==NULL) exit(-1);

admin ad;

while (fread(&ad,sizeof (admin),1,p)==1){
    if (ad.getestado()){
    ad.mostrar_admin();
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-";
    cout << endl << endl;
    }

}
fclose(p);
system("pause");
system("cls");
}

void nuevocliente (char *ad) {
system("cls");
cliente cl;

cl.setidusuario(autonumerar(cl,"clientes.dat"));
cl.pedir_cliente();

while (validar_exist(cl,"clientes.dat")){
    system("cls");
    cout << "Usuario ya existente" <<endl;
    cl.pedir_cliente();
}

guardarcliente(cl);
sumar_cliente(ad);
}

void listar_clientes() {
system("cls");
FILE *p=fopen("clientes.dat","rb");
if (p==NULL){
    cout << endl <<"No se han subscripto clientes aun" << endl;
    system("pause");
    system("cls");
    return;
}
cliente cl;

while(fread(&cl,sizeof(cliente),1,p)==1){
    if(cl.getestado()){
    cl.mostrar_cliente();
    cout << "-_-_-_-_-_-_-_-_-_-_-_-_-";
    cout << endl << endl;
    }

}
fclose(p);
system("pause");
system("cls");

}

template <class temp>
void baja_usuario (temp obj , char *direccion){
system("cls");
int n;


FILE *p=fopen(direccion,"rb+");
if (p==NULL){
    cout << "No se ha encontrado el archivo"<< endl;
    system("pause");
    return;
}

cout << "Ingrese ID a dar de baja: "; cin >> n;

while (fread(&obj,sizeof (obj),1,p)==1){

    if (obj.getid()==n){
    obj.setestado(false);
    break;
    }
}

n=ftell(p);
fseek(p,n-sizeof(obj),0);
fwrite(&obj,sizeof(obj),1,p);

fclose(p);

}


#endif // USUARIOS_H_INCLUDED
