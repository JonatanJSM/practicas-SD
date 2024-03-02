package rmi;

public class Yarda implements Convertible {
    private static final float YARDA_A_CM = 91.44f;

    @Override
    public float toCm(float value) {
        return value * YARDA_A_CM;
    }

    @Override
    public float toM(float value) {
        return value * 0.9144f;
    }

    @Override
    public float toKm(float value) {
        return value * 0.0009144f;
    }
}
