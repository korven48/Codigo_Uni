
-------------------------------------------
-- definición de componentes para el multiplexor4a1
-------------------------------------------
--puerta lógica or de cuatro entradas

--puerta lógica and de cuatro entradas
ENTITY and2 IS
  PORT(i1,i2: IN bit; o : OUT bit);
END and2;

ARCHITECTURE comportamiento OF and2 IS
  BEGIN
    o <= i1 and i2;
END comportamiento;

ENTITY xor2 IS
  PORT(i1,i2: IN bit; o : OUT bit);
END xor2;

ARCHITECTURE comportamiento OF xor2 IS
  BEGIN
    o <= i1 xor i2;
END comportamiento;

ENTITY or2 IS
  PORT(i1,i2: IN bit; o : OUT bit);
END or2;

ARCHITECTURE comportamiento OF or2 IS
  BEGIN
    o <= i1 or i2;
END comportamiento;

------------------------------------
--1-bit Full Adder
------------------------------------

ENTITY fulladder1 IS
PORT(	op1,op2,ce: 	IN bit;	 -- entradas de datos
sum,cs : 		out bit); 	-- salida
END fulladder1;

ARCHITECTURE puertas OF fulladder1 IS
--declaración de componentes
  COMPONENT or2 
    	PORT(i1,i2: IN bit; o : OUT bit);
  END COMPONENT;

  COMPONENT and2
    	PORT(i1,i2: IN bit; o : OUT bit);
  END COMPONENT;

  COMPONENT xor2
    	PORT(i1,i2: IN bit; o : OUT bit);
  END COMPONENT;
  
  --declaración de señales internas
  SIGNAL a,b,c: bit;
--empieza el cuerpo de la arquitectura  
BEGIN
  comp1: xor2 PORT MAP(op1,op2,a);
  comp2: and2 PORT MAP(op1,op2,b);
  comp3: and2 PORT MAP(ce,a,c);
  comp4: xor2 PORT MAP(ce,a,sum);
  comp5: xor2 PORT MAP(b,c,cs);

END puertas;

----------------------------------------------
-- multiplexor vectorial
----------------------------------------------

ENTITY fulladder2 IS
PORT(	a1,b1,a0,b0,ce: 	IN bit;	 -- entradas de datos
	s1,s0,cs : 		OUT bit);-- salida
END fulladder2;

ARCHITECTURE puertas OF fulladder2 IS
--declaracion de componentes
  COMPONENT fulladder1
    PORT(op1,op2,ce : IN bit; sum,cs : OUT bit);
  END COMPONENT;
--declaración,en su caso, de señales internas
  
  SIGNAL c1: bit;
  

--empieza el cuerpo de la arquitectura  
  BEGIN
  fulladd1_1: fulladder1 PORT MAP(a0,b0,ce,s0,c1);
  fulladd1_2: fulladder1 PORT MAP(a1,b1,c1,s1,cs);
  -- instanciación y conexión de componentes
END puertas;


