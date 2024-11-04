semaphore sem;

int write(int sector, void* data) {
  void* data_copy;
  data_copy = kmalloc(DATA_SIZE);

  copy_from_user(data, data_copy, size(data_copy));
  
  int target_pista = sector / cantidad_sectores_por_pista();
  int target_sector = sector % cantidad_sectores_por_pista();

  sem_wait(&sem);
  
  OUT(DOR_IO, 1);
  sleep(50);
  
  OUT(ARM, target_pista);
  OUT(SEEK_SECTOR, target_sector);
  
  while( IN(DOR_STATUS) != 1) {}
  while( IN(ARM_STATUS) != 1) {}
  
  escribir_datos(data_copy);
  
  while(!IN(DATA_READY)) {}
  
  OUT(DOR_IO, 0);
  sleep(200);

  sem_signal(&sem);
  
  kfree(data_copy);
  return 0;
}

int driver_init() {
  sema_init(&sem, 0);
}
