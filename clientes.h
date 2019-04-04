#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include "ventas.h"


void buscar_cl_xnom (char *us , cliente &cl){
FILE *p=fopen("clientes.dat","rb");
if (p==NULL) {
    cout << "error de apertura" << endl;
    exit(-1);
}

while (fread(&cl,sizeof(cliente),1,p)==1){
    if (cl.getestado() && strcmp(us,cl.getnombre())==0){
    fclose(p);
    return;
    }
}

fclose(p);

cl.setidusuario(-10);
return;

}



int buscar_id_cl_transaccion(char *us){
FILE *p=fopen("clientes.dat","rb+");
if (p==NULL){
    cout << "ERROR EN EL ARCHIVO" << endl;
    exit(-1);
}

cliente cl;
int id , b;

while (fread(&cl,sizeof(cliente),1,p)==1){
    if (strcmp(cl.getnombre(),us)==0){
     b=ftell(p);
     break;
    }
}
int cant;
cant=cl.getcant_p();
cl.setcant_p(cant+1);
fseek(p,b-sizeof(cliente),0);
fwrite(&cl,sizeof(cliente),1,p);
fclose(p);

return cl.getid();
}

bool check_pel_obt_alq (char *us, pelicula pel){
alquiler alq;
cliente cl;
buscar_cl_xnom(us,cl);

FILE *p=fopen("alquileres.dat","rb");
if (p==NULL) return true;

while(fread(&alq,sizeof(alquiler),1,p)==1){
    if (alq.getidcliente()==cl.getid()){
    if (alq.getidpeli()==pel.getid()){
    if (!alq.getvencimiento())
    fclose(p);
    return true;
    }
    }

}

fclose(p);
return false;

}


bool check_pel_obt_ven (char *us, pelicula pel){
cliente cl;
venta ven;
buscar_cl_xnom(us,cl);

FILE *p=fopen("ventas.dat","rb");
if (p==NULL) return true;

while(fread(&ven,sizeof(venta),1,p)==1){
    if (ven.getidcliente()==cl.getid()){
    if (ven.getidpeli()==pel.getid()){
    fclose(p);
    return true;
    }
    }

}

fclose(p);
return false;
}

void compra (char *us){
system("cls");
FILE *p=fopen("peliculas.dat","rb");
if (p==NULL){
    cout << "NO SE HAN CARGADO PELICULAS AUN"<< endl;
    system("pause");
    return;
}
pelicula pel;
char palabra[30];
cout << "Ingrese el nombre de la pelicula deseada: ";cin.getline(palabra,30);

bool b=true;

while(fread(&pel,sizeof (pelicula),1,p)==1){
    if (strcmp(palabra,pel.getnombre())==0 ){
        if (pel.getestado()){
        b=false;
        break;
        }
    }
}
if (b){
    cout << endl << "Pelicula inexistente " << endl;
    system("pause");
    return;
}else {
mostrarpeli(pel);
}
/**if (check_pel_obt_alq(us,pel) || check_pel_obt_ven(us,pel)){
    cout << endl << "Pelicula ya en posesion " << endl;
    system("pause");
    return;
}**/
int idcl;

idcl=buscar_id_cl_transaccion(us);
fflush(stdin);
realizar_venta(pel.getid(),pel.getp_venta(),pel.getidadmin(),idcl);
sumar_recaudacion(pel.getidadmin(),pel.getp_venta());
cout << endl << "Compra realizada con exito!" << endl;
fclose(p);

system("pause");

}


void alquila (char *us){
system("cls");
FILE *p=fopen("peliculas.dat","rb");
if (p==NULL){
    cout << "NO SE HAN CARGADO PELICULAS AUN"<< endl;
    system("pause");
    return;
}

pelicula pel;
char palabra[30];
int dias;
cout << "Ingrese el nombre de la pelicula deseada: ";cin.getline(palabra,30);
cout << "Cantidad de dias a rentarla: "; pedirdato(&dias);
bool b=false;

while(fread(&pel,sizeof (pelicula),1,p)==1){
    if (strcmp(palabra,pel.getnombre())==0){
        if (pel.getestado()){
        b=true;
        break;
        }
    }
}


if (!b){
    cout <<  endl <<"Pelicula inexistente " << endl;
    system("pause");
    return;
}else {
mostrarpeli(pel);
}

/**if (check_pel_obt_alq(us,pel) || check_pel_obt_ven(us,pel)){
    cout <<  endl <<"Pelicula ya en posesion " << endl;
    system("pause");
    return;
}**/

int idcl;

idcl=buscar_id_cl_transaccion(us);
fflush(stdin);
realizar_alquiler(pel.getid(),pel.getp_alquiler(),pel.getidadmin(),idcl,dias);
fflush(stdin);
sumar_recaudacion(pel.getidadmin(),pel.getp_alquiler());
cout << endl << "Alquiler realizado con exito!" << endl;
fclose(p);

system("pause");

}

void darse_baja(char *us){
system("cls");
FILE *p=fopen("clientes.dat","rb+");
if (p==NULL){
    cout << "error en el archivo" << endl;
    system("pause");
    exit(-1);
}
cliente cl;
int b;

while (fread(&cl,sizeof(cliente),1,p)==1){
    if (strcmp(us,cl.getnombre())==0){
    b=ftell(p);
    cl.setestado(false);
    break;
    }
    }
fseek(p,b-sizeof(cliente),0);
fwrite(&cl,sizeof(cliente),1,p);
fclose(p);

cout << "Dado de baja con exito"<< endl;
system("pause");

}

void listar_ventas_obt (cliente cl){
venta ven;
bool b=true;
pelicula pel;

FILE *p=fopen("ventas.dat","rb");
if (p==NULL){
    cout << "No se han comprado peliculas " << endl;
}else {
while(fread(&ven,sizeof(venta),1,p)==1){
    if(ven.getidcliente()==cl.getid()){
        b=false;
        buscar_peli_xid(ven.getidpeli(),pel);
        mostrarpeli(pel);
    cout << endl << endl;
   }
}
if (b){
   cout << "No se han comprado peliculas" << endl;
}
}
fclose(p);
}

void listar_alq_obt (cliente cl) {

alquiler alq;
bool b=true;
pelicula pel;

FILE *p=fopen("alquileres.dat","rb");
if (p==NULL){
    cout << "No se han alquilado peliculas " << endl;
}else {
while(fread(&alq,sizeof(alquiler),1,p)==1){
    if(alq.getidcliente()==cl.getid() && !alq.getvencimiento()){
        b=false;
        buscar_peli_xid(alq.getidpeli(),pel);
        mostrarpeli(pel);
    cout << endl << endl;
   }
}
if (b){
   cout << "No se han alquilado peliculas" << endl;
}
}
fclose(p);

}



void listar_pelis_obt (char *us){
system("cls");
pelicula pel;
alquiler al;
cliente cl;

buscar_cl_xnom(us,cl);

if (cl.getid()==-10){
    cout << "Cliente Inexistente" << endl;
    system("pause");
    system("cls");
    return;
}

cout << "          Compradas: " << endl;

listar_ventas_obt(cl);

 cout <<endl << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-" << endl <<endl;

cout << "          Alquiladas: " << endl;

listar_alq_obt(cl);

 cout <<endl << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-"<< endl <<endl;

system("pause");
system("cls");
}

void renovar (char *us){
system("cls");
int dias;
cliente cl;
cout << "Ingresar cantidad de dias a renovar: ";pedirdato(&dias);
FILE *p=fopen("clientes.dat","rb+");
if (p==NULL){
    cout << "error en la apertura" << endl;
    exit(-1);
}

while (fread(&cl,sizeof (cliente),1,p)==1){
    if (strcmp(cl.getnombre(),us)==0 && cl.getestado()){
    cl.sumar_dias(dias);
    fseek(p,ftell(p)-sizeof(cliente),0);
    fwrite(&cl,sizeof (cliente),1,p);
    fclose(p);
    cout << endl << "Cuenta renovada correctamente" << endl;
    system("pause");
    system("cls");
    return;
    }

}

system("pause");
system("cls");
}

void listar_pel_xcl (){
system("cls");
cliente cl;
char nom[20];

cout << "Introdusca nombre de cliente: "; cin >> nom;


listar_pelis_obt(nom);

system("pause");
system("cls");
}

void dar_de_alta(){

time_t tiempo;
struct tm *actual;
tiempo=time(NULL);
actual= localtime(&tiempo);


system("cls");
FILE *p=fopen("clientes.dat","rb+");
    if (p==NULL){
        cout << "error en el archivo" << endl;
        system("pause");
        exit(-1);
    }
cliente cl;
    char nombre[30];
    cout<<"Ingrese el Nombre del Usuario:  ";cin.getline(nombre,30);
int b;

while (fread(&cl,sizeof(cliente),1,p)==1){
    if (strcmp(nombre,cl.getnombre())==0){
        b=ftell(p);
        cl.setestado(true);
        break;
    }

}

fseek(p,b-sizeof(cliente),0);

///digo que fecha actual es la de comienzo y la de vencimiento asi cuando se da de alta nuevamente se le asigna lo que diga renovar
cl.setfecha_comienzo(actual->tm_mday,actual->tm_mon+1,actual->tm_year+1900);
cl.setfecha_vencimiento(actual->tm_mday,actual->tm_mon+1,actual->tm_year+1900);

fwrite(&cl,sizeof(cliente),1,p);
fclose(p);

///Renueva la cuenta por x dias
renovar(nombre);
cout << "Dado de alta con exito"<< endl;
system("pause");

}


#endif // CLIENTES_H_INCLUDED
