N = cantidadHeladeras;
puertaHeladera = sem(1);
turnoHeladera[N] = [sem(0) for _ in range(N)]
turnoHeladera[0].signal();
permisoEnvase[2] = [(sem(0), sem(0))]

cerveza(i, tipoEnvase) {
  llegarABar();
  permisoEnvase[tipoEnvase].wait();
  puertaHeladera.wait();
  
  MeMetenEnHeladera();
  yaMeti.signal();
}


heladera(i) {
  turnoHeladera[i].wait();
  permisoEnvase[0].signal(15);
  permisoENvase[1].signal(10);
  EnchufarHeladera();
  restantes = 25;
  while (restantes > 0) {
    AbrirHeladera();
    puertaHeladera.signal();

    yaMeti.wait();
    cerrarHeladera();
    restantes--;
  }
  enfrioRapido();
  if (i != N - 1) turnoHeladera[i + 1].signal();
  return 0;
}
