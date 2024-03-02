struct inputs{
    float numero;
    char unidadMedida;
};

program CONVERTIDOR_PROG{
    version CONVERTIDOR_VER{
        float conversion(inputs) = 1;
    } = 1;
} = 0x2fffffff;