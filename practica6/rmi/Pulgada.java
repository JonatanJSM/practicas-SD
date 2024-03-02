package rmi;

public class Pulgada implements Convertible {
    private static final float PULGADA_A_CM = 2.54f;

    @Override
    public float toCm(float value) {
        return value * PULGADA_A_CM;
    }

    @Override
    public float toM(float value) {
        return toCm(value) / 100;
    }

    @Override
    public float toKm(float value) {
        return toCm(value) / 100000;
    }
}
