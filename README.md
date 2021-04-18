# SOR-Semáforos-1S-2021
Trabajo Práctico Semáforos primer semestre año 2021

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
          V(sem_mezclar)
          -------------
          cortarExtra()()                  
          ----------------
          P(sem_mezclar)
          mezclar()
          V(sem_salar)
          ----------------
          P(sem_salar)
          mutex()
          salar()
          mutex()
          V(sem_usoSarten)
          ----------------
          P(sem_usoSarten)
          mutex()
          usoSarten()
          mutex()
          V(sem_hornearPan)
          -----------------
           P(sem_hornearPan)
          mutex()
          hornearPan()
          mutex()
          V(sem_armarSandwich)
          ------------------
           P(sem_armarSandwich)
          mutex()
          armarSandwich()
          mutex() 
          
          
          
          
