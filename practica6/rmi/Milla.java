package rmi;

public class Milla implements Convertible {
    private static final float MILLA_A_KM = 1.60934f;

    @Override
    public float toCm(float value) {
        return value * 160934; // 1 milla = 160934 cm
    }

    @Override
    public float toM(float value) {
        return value * 1609.34f; // 1 milla = 1609.34 m
    }

    @Override
    public float toKm(float value) {
        return value * MILLA_A_KM;
    }
}
