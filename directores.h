#ifndef DIRECTORES_H_INCLUDED
#define DIRECTORES_H_INCLUDED



void mostrardir (director dir){
cout << "ID: " << dir.getid() << endl;
cout << "NOMBRE: " << dir.getnombre() << endl;
cout << "APELLIDO: " << dir.getapellido() << endl;
cout << "FECHA DE NACIMIENTO: " << dir.getdia() << "/" << dir.getmes() << "/" << dir.getanio() << endl;
cout << "EDAD: " << dir.getedad() << endl;
}


void listar_dir_id (){
system("cls");
FILE *p=fopen("directores.dat","rb");
if (p==NULL) {
    cout << "NO SE HAN CARGADO DIRECTORES AUN" << endl;
    system("pause");
    return;
}
director dir;
int id;
cout << "Ingrese ID de director a buscar ";
cin>> id;

while (fread(&dir,sizeof (director),1,p)==1){
    if (dir.getid()==id){
        if (dir.getestado()){
        mostrardir(dir);
        cout << endl;
        system("pause");
        fclose(p);
        return;
        }
    }
}

}


void baja_director () {
system("cls");
FILE *p=fopen("directores.dat","rb+");
if (p==NULL){
    cout << "NO SE HAN CARGADO DIRECTORES AUN" << endl;
    system("pause");
    return;
}
director dir;
int id;
cout << "Ingrese ID de director a dar de baja: "; cin >> id;
cout << endl ;

while(fread(&dir,sizeof(director),1,p)==1){
    if (id==dir.getid()){
        mostrardir(dir);
        cout << endl << endl<< endl << "Este director se ha dado de baja"<<endl;
        dir.setestado(false);
        break;
    }

}
int b=ftell(p);
fseek(p,b-sizeof(director),0);
fwrite(&dir,sizeof(director),1,p);
fclose(p);
system("pause");
}

void editar_dir (){
system("cls");
bool vuelta , f=true;
FILE *p=fopen("directores.dat","rb+");
if (p==NULL){cout << "NO SE HAN CARGADO DIRECTORES AUN" << endl;

system("pause");
return;
}
int id;
cout << "Ingrese ID de director a modificar: ";cin >> id;
director dir;
while(fread(&dir,sizeof(director),1,p)==1){
    if (dir.getid()==id && dir.getestado()){
        cout << endl;
        f=false;
        mostrardir(dir);
        break;
    }


}

if (f) {
    cout << endl << "DIRECTOR NO ENCONTRADO" << endl << endl;
    system("pause");
    return;
}
int d,m,a;
do {

cout << "Ingrese nueva fecha de nacimiento" << endl;
cout << "Dia: ";pedirdato(&d);
cout << "Mes: ";pedirdato(&m);
cout << "Anio: ";pedirdato(&a);

while (!dir.setfechanac(d,m,a)){
    cout << "Fecha incorrecta , intentelo de nuevo" << endl;
    cout << "Dia: ";pedirdato(&d);
    cout << "Mes: ";pedirdato(&m);
    cout << "Anio: ";pedirdato(&a);

}

dir.calcularedad();

if (dir.getedad()>=18 && dir.getedad()<=100){
    vuelta=false;
}else {vuelta=true;
    cout << "Edad incorrecta" << endl << endl;
    }

}while(vuelta);

int b=ftell(p);
fseek(p,b-sizeof(director),0);
fwrite(&dir,sizeof(director),1,p);
system("cls");
cout << "Director modificado correctamente" << endl << endl;
mostrardir(dir);
cout << endl;
system("pause");
fclose(p);

}

bool validar_dir_id(int id){
FILE *p=fopen("directores.dat","rb");
if (p==NULL) exit(-1);
director dir;
while (fread(&dir,sizeof(director),1,p)==1){
    if (dir.getid()==id){
     fclose(p);
     return true;
    }
}
fclose(p);
return false;
}

void nuevodirector () {

director dir;

FILE *p;

do {
system("cls");
dir.pedir_director();


}while(validar_exist(dir,"directores.dat"));


p=fopen("directores.dat","ab");
if (p==NULL){cout << "FALLO EN EL ARCHIVO";exit(-1);}

fwrite(&dir,sizeof(director),1,p);

fclose(p);
system("cls");
}

void listardirectores () {
system("cls");
FILE *d;
director dir;

d=fopen("directores.dat","rb");
if (d==NULL){cout << "FALLO DE ARCHIVO";exit(-1);}


while(fread(&dir,sizeof (director),1,d)==1){
cout << endl << endl;
if (dir.getestado()){
mostrardir(dir);
}
}
fclose(d);
system("pause");
system("cls");
}


#include "menues.h"





#endif // DIRECTORES_H_INCLUDED
