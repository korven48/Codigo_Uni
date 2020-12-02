-------------------------------------------
-- definición de puertas para el multiplexor4a1
-------------------------------------------
--puerta lógica or de cuatro entradas
ENTITY or4 IS
  PORT(i1, i2,i3,i4 : IN bit; o : OUT bit);
END or4;

ARCHITECTURE comportamiento OF or4 IS
BEGIN
  o <= i1 OR i2 OR i3 OR i4;
END comportamiento;

--puerta lógica and de cuatro entradas
ENTITY and4 IS
  PORT(i1, i2,i3,i4 : IN bit; o : OUT bit);
END and4;

ARCHITECTURE comportamiento OF and4 IS
BEGIN
   o <= i1 and i2 and i3 and i4;
END comportamiento;

--puerta lógica inv de dos entradas
ENTITY inv IS
  PORT(i1 : IN bit; o : OUT bit);
END inv;

ARCHITECTURE comportamiento OF inv IS
BEGIN
  o <= not i1;
END comportamiento;



ENTITY multiplexor4a1 IS
PORT(	X0, X1,X2, X3: 	IN bit;	 -- entradas de datos
S1,S0 : 		IN bit; 	-- entradas de control
E:		IN bit;	--entrada de capacitación
Z : 		OUT bit);-- salida
END multiplexor4a1;

ARCHITECTURE puertas OF multiplexor4a1 IS
--declaración de componentes
  COMPONENT or4 
    	PORT(i1, i2,i3,i4 : IN bit; o : OUT bit);
  END COMPONENT;
  COMPONENT and4
    	PORT(i1, i2, i3,i4 : IN bit; o : OUT bit);
  END COMPONENT;
  COMPONENT inv
   	 PORT(i1 : IN bit; o : OUT bit);
  END COMPONENT;
  
  --declaración de señales internas
  SIGNAL ia1,ia2,ao1,ao2,ao3,ao4: bit;
--empieza el cuerpo de la arquitectura  
BEGIN
  i_inv_1 : inv  PORT MAP(s1, ia1);
  i_inv_2 : inv  PORT MAP(s0, ia2);

  i_and_1 : and4  PORT MAP(ia1,ia2,x0,e,ao1);
  i_and_2 : and4  PORT MAP(ia1,s0, x1,e,ao2);
  i_and_3 : and4  PORT MAP(s1,ia2,x2,e,ao3);
  i_and_4 : and4  PORT MAP(s1,s0,x3,e,ao4);

  i_or_1  : or4   PORT MAP(ao1,ao2,ao3,ao4,z);

END puertas;
