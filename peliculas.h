#ifndef PELICULAS_H_INCLUDED
#define PELICULAS_H_INCLUDED

int cant_pel(){
FILE *p=fopen("peliculas.dat","rb");
if (p==NULL){
    cout << "No se han registrado peliculas"<<endl;
    return 0;
}
int c;
fseek(p,0,2);
c=ftell(p)/sizeof(pelicula);
fclose(p);
return c;
}


void buscar_peli_xid (int id , pelicula &pel){
FILE *p=fopen("peliculas.dat","rb");
if (p==NULL)exit(-1);

while(fread(&pel,sizeof(pelicula),1,p)==1){
    if (pel.getid()==id){
        if (pel.getestado()){
            fclose(p);
            return;
        }
    }

}

}

void sumar_pelicula(char *us){
FILE *p=fopen("admins.dat","rb+");
if (p==NULL) exit(-1);
admin ad;
int b;

while (fread(&ad,sizeof(admin),1,p)==1){
    if (strcmp(ad.getnombre(),us)==0){
    ad.setcantpeliculas(ad.getcantpeliculas()+1);
    b=ftell(p);
    fseek(p,b-sizeof(admin),0);
    fwrite(&ad,sizeof (admin),1,p);
    fclose(p);
    }
}
}

void mostrarpeli (pelicula pel){
cout << "ID: " << pel.getid()<<endl;
cout <<"Nombre: "<< pel.getnombre()<<endl;
cout << "Genero: "<< pel.getgenero()<<endl;
cout << "Precio de vents: "<< pel.getp_venta()<<endl;
cout << "Precio de alquiler: " << pel.getp_alquiler() << endl;
cout << "Duracion: "<< pel.getduracion()<<endl;
cout << "ID de Director: "<< pel.getiddir()<<endl;
}


void newpelicula (char *us) {

pelicula pel;
bool b=false;

pel.setidpeli(autonumerar(pel,"peliculas.dat"));
pel.setidadmin(buscar_id_admin(us));

do{
system("cls");
if (b) cout << "Registro ya existente " << endl;

pel.pedir_pel();

b=validar_exist(pel,"peliculas.dat");


}while(b);

cout << endl << endl << endl;
mostrarpeli(pel);


FILE *p;
p=fopen("peliculas.dat","ab");
if (p==NULL){
    cout << "ERROR AL ABRIR EL ARCHIVO0" << endl;
    system("pause");
    return;
}
cout << endl << endl << endl;
fwrite(&pel,sizeof (pelicula),1,p);
cout << endl << endl << endl;
fclose(p);
sumar_pelicula(us);
system("pause");
system("cls");
}

void editar_pel () {
system("cls");
FILE *p=fopen("peliculas.dat","rb+");
if (p==NULL){
    cout << "NO SE HAN CARGADO PELICULAS" << endl;
    system("pause");
    return;
}
int id;
int b;
pelicula pel;
cout << "Ingrese ID de pelicula a modificar: "; cin >> id;


while(fread(&pel,sizeof (pelicula),1,p)==1){
    if (id==pel.getid()){
    cout << endl << endl;
    mostrarpeli(pel);
    b=ftell(p);
    break;
    }
}
float precio;
cout << endl << "Ingrese nuevo precio de venta: ";cin >> precio;
pel.setp_venta(precio);
cout << "Ingrese nuevo precio de alquiler: ";cin >> precio;
pel.setp_alquieler(precio);

fseek(p,b-sizeof(pelicula),0);
fwrite(&pel,sizeof(pelicula),1,p);
system("cls");
fclose(p);
cout << "Pelicula modificada correctamente"<<endl;
mostrarpeli(pel);
cout << endl;
system("pause");

}


void listarpeliculas () {
system("cls");
pelicula pel;
FILE *d;

d=fopen("peliculas.dat","rb");
if (d==NULL){cout << "NO SE HAN REGISTRADO PELICULAS";
system("pause");
return;}


while(fread(&pel,sizeof (pelicula),1,d)==1){
cout << endl << endl;
if (pel.getestado()){
mostrarpeli(pel);
cout << "-_-_-_-_-_-_-_-_-_-_-_-_";
cout << endl << endl;
}
}
fclose(d);
system("pause");
system("cls");

}


void listar_pelicula(){
system("cls");
FILE *p=fopen("peliculas.dat","rb");
if (p==NULL){
    cout << "CATALOGO VACIO"<< endl;
    system("pause");
    return;
}

pelicula pel;
char nombre[30];

cout << "Ingrese nombre de pelicula a buscar: ";cin.getline(nombre,30);


while (fread(&pel,sizeof (pelicula),1,p)==1){
    if (strcmp(pel.getnombre(),nombre)==0){
        if (pel.getestado()){
    mostrarpeli(pel);
    cout << endl;
    system("pause");
    fclose(p);
    return;
    }
    }
}
cout << "Pelicula inexistente" << endl;
fclose(p);
system("pause");
system("cls");
}

void listar_pel_xnom(){
system("cls");
char nombre[30];
pelicula pel;
cout << "Nombre de Pelicula a buscar: "; cin.getline(nombre,30);

FILE *p=fopen("peliculas.dat","rb");
if (p==NULL){
    cout << "No se ha encontrado la pelicula " << endl;
    system("pause");
    return;
}

while (fread(&pel,sizeof(pelicula),1,p)==1){
    if (pel.getestado() && strcmp(nombre,pel.getnombre())==0){
        mostrarpeli(pel);
        cout << endl;
        system("pause");
        fclose(p);
        return;
    }
}

fclose(p);
cout << "No se ha encontrado la pelicula" << endl;


system("pause");
system("cls");
}

void listar_pel_xgenero (){
system("cls");
char nombre[30];
pelicula pel;
cout << "Genero de Pelicula a buscar: "; cin >> nombre;

FILE *p=fopen("peliculas.dat","rb");
if (p==NULL){
    cout << "No se ha encontrado la pelicula " << endl;
    system("pause");
    return;
}

while (fread(&pel,sizeof(pelicula),1,p)==1){
    if (pel.getestado() && strcmp(nombre,pel.getgenero())==0){
        mostrarpeli(pel);
        cout << endl;
        system("pause");
        fclose(p);
        return;
    }
}

fclose(p);
cout << "No se ha encontrado la pelicula" << endl;


system("pause");
system("cls");


}

void baja_pelicula(){
system("cls");
int id,b;

cout << "Ingrese ID de pelicula a borrar: ";pedirdato(&id);

FILE *p=fopen("peliculas.dat","rb+");
if (p==NULL) {
    cout << "NO SE HAN CARGADO PELICULAS" << endl;
    system("pause");
    return;
}
pelicula pel;

while (fread(&pel,sizeof(pelicula),1,p)==1){
    if (pel.getid()==id){
    pel.setestado(false);
    b=ftell(p);
    break;
    }
}

fseek(p,b-sizeof(pelicula),0);
fwrite(&pel,sizeof(pelicula),1,p);

fclose(p);

cout << endl << endl << "Pelicula borrada exitosamente" << endl<<endl;
system("pause");
system("cls");
}





#endif // PELICULAS_H_INCLUDED
