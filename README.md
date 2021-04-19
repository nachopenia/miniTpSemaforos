# SOR-Semáforos-1S-2021
Trabajo Práctico Semáforos primer semestre año 2021

Ignacio Peña - dni 41262099

Pseudocodigo subway argento:
  
  4 equipos. 
  un equipo a la vez usa: sarten, sal, horno
     
     acciones:
            -cortar dientes de ajo, un puñado de peregil
            -mezclar con huevo
            -salar
            -cocinar en sarten por 5'
            -Hornear pan
            -cortar extras (lechuga, tomate, cebolla, pepino)
            -armar sandwich
            
          cortar()
          V(sem_mezclar)  //asigno semaforo en V para sumar 1 y habilitar mezclar.
          -------------
          cortarExtra()()   // no necesita ningun semaforo ya que en cualquier momento se pueden cortar la lechuga y tomate.              
          ----------------
          P(sem_mezclar)   // al entrar en mezclar el semaforo P restara uno y es posible ingresar porque el paso anterior fue realizado
          mezclar()
          V(sem_salar)  // sumo 1 en el semaforo para habilitar la siguiente accion.
          ----------------
          P(sem_salar) // resto 1 para ingresar
          mutex()    // me encuentro con un mutex, ya que esta accion se puede realizar de un equipo a la vez.
          salar()
          mutex()  //una vez terminado retiro el mutex para que otro pueda entrar
          V(sem_usoSarten)  // sumo 1 en el semaforo para habilitar la siguiente accion.
          ----------------
          P(sem_usoSarten)  //resto 1 para ingresar
          mutex()  //me encuentro con un mutex, ya que esta accion se puede realizar de un equipo a la vez.
          usoSarten()
          mutex() // una vez terminado retiro el mutex para que otro pueda entrar
          V(sem_hornearPan) //sumo 1 en el semaforo para habilitar la siguiente accion.
          -----------------
           P(sem_hornearPan)
          mutex() // me encuentro con un mutex, ya que esta accion se puede realizar de un equipo a la vez.
          hornearPan()
          mutex() //una vez terminado retiro el mutex para que otro pueda entrar
          V(sem_armarSandwich) // sumo 1 en el semaforo para habilitar la siguiente accion.
          ------------------
           P(sem_armarSandwich) //resto 1 para ingresar en el final que es armar el sandwich
          armarSandwich()
    
          
          informe: 
          
          Me encontre con la dificultad de no saber nada de C. Se me complico bastante el tp, investigue por muchos lados y no encontraba solucion, en un momento llegue 
          a lograr que se ordene un poco el programa. Investigando y viendo videos pude avanzar, no pude realizar la lectura de archivos, ya que no entendi como dividir
          los elementos de los archivos y luego poder utlilizarlos del mismo modo que escribiendolos yo mismo.
          
          
          
