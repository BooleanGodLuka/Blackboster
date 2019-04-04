#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED

void cargar_vec_pel (int *v , bool &b){
alquiler alq;
venta ven;
FILE *p=fopen("ventas.dat","rb");
if (p==NULL){
    cout << "No se han registrado ventas" <<endl;
    fclose(p);
}else {
b=false;
while(fread(&ven,sizeof (venta),1,p)==1){
    if (ven.getestado()){
    v[ven.getidpeli()-1]++;
    }
}
fclose(p);
}

p=fopen("alquileres.dat","rb");
if (p==NULL){
    cout << "No se han registrado alquileres" << endl;
    fclose(p);
}else {
b=false;
while(fread(&alq,sizeof(alquiler),1,p)==1){
    if (alq.getestado()){
    v[alq.getidpeli()-1]++;
    }
}
fclose(p);
}

}

void pel_menos_ven () {
system("cls");
int *v , c;
pelicula pel;
bool b=true;
c=cant_pel();
if (c==0){
    cout << "No hay peliculas" << endl;
    system("pause");
    system("cls");
    return;
}

v= new int[c];

cargar_vec_pel(v,b);

if (b){
    cout << endl << endl << "No se han registrado transacciones de ningun tipo" <<endl;
}else {
int posmen , valmen;

for (int i=0; i<c;i++){
    if (i==0){
    posmen=0;
    valmen=v[0];
    }else if (v[i]<valmen){
    valmen=v[i];
    posmen=i;
    }
}
buscar_peli_xid(posmen,pel);
mostrarpeli(pel);

for (int j=0;j<c;j++){
    if (v[j]==valmen && !(j==posmen)){
    cout << endl <<endl<<endl <<"Tambien cuenta con el mismo valor: " << endl <<endl;
    buscar_peli_xid(j,pel);
    mostrarpeli(pel);
    }
}

}
delete []v;
system("pause");
system("cls");
}

void pel_mas_ven () {
system("cls");
int *v , c;
pelicula pel;
bool b=true;
c=cant_pel();
if (c==0){
    cout << "No hay peliculas" << endl;
    system("pause");
    system("cls");
    return;
}

v= new int[c];

cargar_vec_pel(v,b);


if (b) {
    cout << "No se han hecho transaccion alguna" << endl;
}else {
int posmay , valmay;

for (int i=0;i<c;i++){
    if (i==0){
    posmay=v[0];
    valmay=0;
    }else if (v[i]>valmay) {
    valmay=v[i];
    posmay=i;
    }
}
buscar_peli_xid(posmay,pel);
mostrarpeli(pel);
cout << endl <<endl<<endl;
for (int j=0;j<c;j++){
    if (v[j]==valmay && !(j==posmay)){
    cout << "Tambien cuenta con el mismo valor: " << endl << endl;
    buscar_peli_xid(j,pel);
    mostrarpeli(pel);
    }
}
}
delete []v;
system("pause");
system("cls");
}



void recau_total () {
system("cls");
venta ven;
alquiler alq;
float val;

cout << "Valor recaudado en ventas: ";
val=val_transaccion(ven,"ventas.dat");
cout << val << endl << endl << endl;

cout << "Valor recaudado en alquileres: ";
val=val_transaccion(alq,"alquileres.dat");
cout << val << endl << endl << endl;


system("pause");
system("cls");
}

void recau_xpel() {
system("cls");
venta ven;
alquiler alq;
float val;
int id;

cout << "Ingrese ID de pelicula a consultar: "; pedirdato(&id);

cout << "Valor recaudado en ventas: ";
val=val_transaccion(ven,"ventas.dat",id);
cout << val << endl << endl << endl;

cout << "Valor recaudado en alquileres: ";
val=val_transaccion(alq,"alquileres.dat",id);
cout << val << endl << endl << endl;


system("pause");
system("cls");


}

void recau_xcl () {
system("cls");
venta ven;
alquiler alq;
float val;
int id;

cout << "Ingrese ID de cliente a consultar: "; pedirdato(&id);

cout << "Valor recaudado en ventas: ";
val=val_transaccion(ven,"ventas.dat",-10,-10,id);
cout << val << endl << endl << endl;

cout << "Valor recaudado en alquileres: ";
val=val_transaccion(alq,"alquileres.dat",-10,-10,id);
cout << val << endl << endl << endl;


system("pause");
system("cls");

}

void recau_xadmin () {
system("cls");
venta ven;
alquiler alq;
float val;
int id;

cout << "Ingrese ID de admin a consultar: "; pedirdato(&id);

cout << "Valor recaudado en ventas: ";
val=val_transaccion(ven,"ventas.dat",-10,id);
cout << val << endl << endl << endl;

cout << "Valor recaudado en alquileres: ";
val=val_transaccion(alq,"alquileres.dat",-10,id);
cout << val << endl << endl << endl;


system("pause");
system("cls");

}

#endif // REPORTES_H_INCLUDED
