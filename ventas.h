#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED


void sumar_recaudacion (int id,float importe){
FILE *p=fopen("admins.dat","rb+");
if (p==NULL){
    cout << "error en el archivo"<< endl;
    system("pause");
    exit(-1);
}
admin ad;
int b;

while (fread(&ad,sizeof (admin),1,p)==1){
    if (ad.getid()==id){
        b=ftell(p);
        break;
    }
}
float vr=0;
vr=ad.getvalor_recaudado();
ad.setvalor_recaudado(vr+=importe);
fseek(p,b-sizeof(admin),0);
fwrite(&ad,sizeof(admin),1,p);
fclose(p);
}




void realizar_venta (int idpeli, float importe , int idad,int idcl) {

venta ven;
time_t tiempo;
struct tm *actual;

tiempo=time(NULL);
actual= localtime(&tiempo);


ven.setestado(true);
fflush(stdin);
ven.setfecha(actual->tm_mday,actual->tm_mon+1,actual->tm_year+1900);
ven.setidadmin(idad);
ven.setidcliente(idcl);
ven.setidpeli(idpeli);
ven.setidventa(autonumerar(ven,"ventas.dat"));
ven.setimporte(importe);

FILE *p=fopen("ventas.dat","ab");
if (p==NULL) {
    cout << "error de apertura" << endl;
    exit(-1);
}
fwrite(&ven,sizeof(venta),1,p);
fclose(p);

}

void realizar_alquiler (int idpeli, float importe , int idad,int idcl, int dias) {

time_t tiempo;
struct tm *actual;

tiempo=time(NULL);
actual= localtime(&tiempo);

alquiler al;

al.setdias(dias);
al.setestado(true);
al.setfecha_inicio(actual->tm_mday,actual->tm_mon+1,actual->tm_year+1900);
al.setfecha_final();
al.setidadmin(idad);
al.setidalquiler(autonumerar(al,"alquileres.dat"));
al.setidcliente(idcl);
al.setidpeli(idpeli);
al.setimporte(importe*dias);
al.setvencimiento(false);
FILE *p=fopen("alquileres.dat","ab");
if (p==NULL) {
    cout << "error de apertura" << endl;
    exit(-1);
}
fwrite(&al,sizeof(alquiler),1,p);
fclose(p);

}

void listar_ven () {
system("cls");
venta ven;
alquiler al;
FILE *p=fopen("ventas.dat","rb");
cout << "            Ventas: "<< endl;
if (p==NULL){
    cout << "No se han registrado compras" << endl;
}

while (fread(&ven,sizeof(venta),1,p)==1){
    if (ven.getestado()) {
        ven.mostrar_venta();
        cout << endl << "***************************" << endl <<endl;
    }
}
fclose(p);
cout << endl << endl;


p=fopen("alquileres.dat","rb");
cout << "              Alquileres: "<<endl;

if (p==NULL){
    cout << "No se han registrado alquileres" << endl;
}

while (fread(&al,sizeof(alquiler),1,p)==1){
    if (al.getestado()) {
        if (!al.getvencimiento()) {
        al.mostrar_alq();
        cout << endl << "***************************" << endl <<endl;
    }
    }
}
fclose(p);

system("pause");
system("cls");
}

void listar_ven_xid (){
system("cls");
FILE *p;
alquiler alq;
venta ven;
char op;
int id;
bool vuelta=true,e=true;



while (vuelta){
cout << "Ingrese 1 para bucar ventas o 2 para alquileres: ";cin >> op;
switch(op){
case '1':
cout << "ID de venta a buscar: "; cin >> op;
p=fopen("ventas.dat","rb");
cout << "            Venta: ";
if (p==NULL){
    cout << "No se han registrado compras" << endl;
    system("pause");
    return;
}

while (fread(&ven,sizeof(venta),1,p)==1){
    if (ven.getestado() && ven.getid()==id) {
        e=false;
        ven.mostrar_venta();
        cout << endl <<endl;
    }
}
fclose(p);

if (e){
    cout << endl <<"Venta Inexistente" << endl;
}


vuelta=!vuelta;
break;



case '2':
cout << "Ingrese ID de alquiler a buscar: "; cin >> id;
p=fopen("alquileres.dat","rb");
cout << "             Alquileres: "<<endl;
if (p==NULL){
    cout << "No se han registrado alquileres" << endl;
    system("pause");
    return;
}

while (fread(&alq,sizeof(alquiler),1,p)==1){
    if (alq.getestado() && alq.getidalquiler()==id ){
        if (!alq.getvencimiento()) {
    e=false;
    alq.mostrar_alq();
    cout << endl << endl;
        }
    }
}
fclose(p);
if (e)cout << "Alquiler inexistente" <<endl;

vuelta=!vuelta;
break;


default:
cout << "Opcion incorrecta" << endl;
system("pause");
system("cls");
break;
}
}
system("pause");
system("cls");
}

void listar_ven_xcl (){
system("cls");
venta ven;
alquiler alq;
int id;
bool e=true;
cout << "ID de cliente: ";cin >> id;
FILE *p=fopen("ventas.dat","rb");
cout << "            Ventas: ";
if (p==NULL){
    cout << "No se han registrado compras" << endl;
    e=false;
}

while (fread(&ven,sizeof(venta),1,p)==1){
    if (ven.getestado() && ven.getidcliente()==id) {
        e=false;
        ven.mostrar_venta();
        cout << endl <<endl;
    }
}
fclose(p);
if (e) cout << "El cliente no ha realizado compras" << endl;
cout << endl << endl<<endl;
cout << "********************************" <<endl <<endl ;

cout << "            Alquileres: ";
e=true;
p=fopen("alquileres.dat","rb");
if (p==NULL) {
    cout << "No se han registrado alquileres"<<endl;
    e=false;
}

while(fread(&alq,sizeof(alquiler),1,p)==1){
    if (alq.getestado() && alq.getidcliente()==id){
        if (!alq.getvencimiento()){
    e=false;
    alq.mostrar_alq();
    cout << endl << endl;
    }}

}

fclose(p);
if (e)cout << "El cliente no ha realizado alquileres" <<endl;

system("pause");
system("cls");
}

void listar_ven_xpel(){
system("cls");
venta ven;
alquiler alq;
bool e=true;

int id;
cout << "ID de pelicula: ";cin >> id;

FILE *p=fopen("ventas.dat","rb");

cout << "            Ventas: ";
if (p==NULL){
    cout << "No se han registrado compras" << endl<<endl;
    e=false;
}

while (fread(&ven,sizeof(venta),1,p)==1){
    if (ven.getestado() && ven.getidpeli()==id) {
        e=false;
        ven.mostrar_venta();
        cout << endl <<endl;
    }
}
fclose(p);
if (e) cout <<"Esta pelicula no se ha vendido" << endl;



e=true;
cout << endl <<endl;
cout << "              Alquileres:"<<endl<<endl;
p=fopen("alquileres.dat","rb");
if (p==NULL){
    cout << "No se han registrado alquileres" << endl;
    e=false;
}

while(fread(&alq,sizeof(alquiler),1,p)==1){
    if (alq.getestado() && alq.getidpeli()==id){
        if (!alq.getvencimiento()) {
    e=false;
    alq.mostrar_alq();
    cout << endl << endl;
    }}
}
fclose(p);
if (e) cout << "Esta pelicula no se ha alquilado" <<endl;

system("pause");
system("cls");
}

void listar_ven_xdir (){
system("cls");
venta ven;
pelicula pel;
alquiler alq;
bool e=true;
int id;
cout << "ID de director: ";cin >> id;


FILE *p=fopen("ventas.dat","rb");
cout << "            Ventas: ";
if (p==NULL){
    cout << "No se han registrado compras" << endl<<endl;
    e=false;
}

while (fread(&ven,sizeof(venta),1,p)==1){
    if (ven.getestado()) {
        buscar_peli_xid(ven.getidpeli(),pel);
        if (pel.getiddir()==id){
        e=false;
        ven.mostrar_venta();
        cout << endl <<endl;
        }
    }
}
fclose(p);
if (e) cout << "No hay ventas de este director" << endl;



e=true;
cout << endl << endl;

cout << "               Alquileres:"<<endl;
p=fopen("alquileres.dat","rb");
if(p==NULL){
    cout << "No se han registrado alquileres"<<endl;
    e=false;
}

while(fread(&alq,sizeof(alquiler),1,p)==1){
    if (alq.getestado() ){
        if (!alq.getvencimiento()) {
    buscar_peli_xid(alq.getidpeli(),pel);
    if (pel.getid()==id){
    e=false;
    alq.mostrar_alq();
    cout << endl <<endl;
    }
    }}
}
fclose(p);
if (e) cout << "No hay alquileres de este director"<<endl;
system("pause");
system("cls");
}
#endif // VENTAS_H_INCLUDED
