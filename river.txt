heladeraActual = 0;
puertaHeladera = sem(1);
heladeraRestante[N][2] //all initialized to [15, 10]. 
mutexHeladeraRestante = sem(1)

// tipoEnvase = 0 means bottles and tipoEnvase = 1 means "porrones" (which is kind of a glass)
cerveza(i, tipoEnvase) {
  llegarABar();

  mutex.wait();
  
  if (heladeraRestante[heladeraActual][tipoEnvase] <= 0) {
    return;
  }

  puertaHeladera.wait();
  
  heladeraRestante[heladeraActual][tipoEnvase]--;
  mutex.signal();
  MeMetenEnHeladera();
  yaMeti.signal();
}


heladera(i) {
  EnchufarHeladera();
  while (true) {
    AbrirHeladera();
    puertaHeladera.signal();

    yaMeti.wait();
    cerrarHeladera();
    mutex.wait() 
    if (heladeraRestante[heladeraActual][0] == 0 && heladeraRestante[heladeraActual][1] == 0) {
      break;
    }
    mutex.signal();
  }
  enfrioRapido();
  mutex.wait();
  heladeraActual++;
  mutex.signal();
}
