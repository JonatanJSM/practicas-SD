package rmi;

public class Pie implements Convertible {
    private static final float PIE_A_CM = 30.48f;

    @Override
    public float toCm(float value) {
        return value * PIE_A_CM;
    }

    @Override
    public float toM(float value) {
        return value * 0.3048f;
    }

    @Override
    public float toKm(float value) {
        return value * 0.0003048f;
    }
}
