# Experiment 01 — DC Motor Open-Loop Characterization

**Project:** Arduino-Based DC Motor Speed Controller  
**Platform:** Arduino Uno + L293D + DC Motor with Encoder  
**Environment:** Tinkercad Circuits  
**Status:** Completed

---

## 1. Objective

Characterize the relationship between PWM input and DC motor rotational speed to establish the motor's operating range and obtain baseline data for subsequent closed-loop controller development.

## 2. Hardware Configuration

| Component | Configuration |
|---|---|
| Microcontroller | Arduino Uno R3 |
| Motor Driver | L293D |
| Motor | DC Motor with Encoder |
| PWM Control | Digital Pin 9 |
| Motor Direction | Digital Pins 7, 8 |
| Encoder Channel A | Digital Pin 2 |
| Encoder Pulses per Revolution | 227.2 (empirical estimate) |
| Power Supply | Tinkercad simulation supply |

## 3. Experimental Methodology

The motor was operated in open-loop mode, meaning no feedback control was applied to regulate its speed.

PWM values were applied directly to the motor driver while encoder pulses were measured to calculate rotational speed.

| Parameter | Value |
|---|---:|
| PWM Test Values | 100, 130, 160, 190, 220, 255 |
| Test Duration per Setting | 5 seconds |
| Sampling Interval | 100 ms |
| Stabilization Period | 1 second |
| Encoder Counting Method | Rising-edge interrupt |
| Speed Measurement | Encoder-based RPM calculation |

**RPM Calculation:**

\[
RPM = \frac{N \times 60}{PPR \times \Delta t}
\]

Where:

- \(N\) = Encoder pulses counted during the sampling interval
- \(PPR\) = Encoder pulses per revolution
- \(\Delta t\) = Sampling interval in seconds

## 4. Experimental Results

| Test | PWM Input | Average Speed (RPM) |
|---:|---:|---:|
| 1 | 100 | 58.29 |
| 2 | 130 | 75.82 |
| 3 | 160 | 92.68 |
| 4 | 190 | 109.49 |
| 5 | 220 | 127.31 |
| 6 | 255 | 147.44 |

### Observed Relationship

Motor speed increased consistently with increasing PWM input.

| Observation | Finding |
|---|---|
| Minimum tested PWM | 100 |
| Speed at PWM 100 | 58.29 RPM |
| Maximum tested PWM | 255 |
| Maximum measured speed | 147.44 RPM |
| General PWM-Speed Relationship | Approximately linear |

## 5. Engineering Analysis

1. **Motor response:** The motor demonstrated a consistent increase in rotational speed as PWM input increased.

2. **Operating range:** The measured operating range was approximately 58–147 RPM for the tested PWM values.

3. **Setpoint feasibility:** The motor demonstrated sufficient speed capability for the previously tested 76, 104, and 123 RPM setpoints. A 151 RPM target exceeded the maximum measured speed.

4. **Controller implications:** Previous PID experiments exhibited substantial tracking errors at 104 and 123 RPM. Since both speeds are achievable in open-loop operation, controller tuning and implementation require further investigation.

5. **Feedforward opportunity:** The measured PWM-to-RPM relationship provides a baseline for estimating the initial PWM command required for a desired motor speed.

## 6. Conclusion

The open-loop characterization established a baseline relationship between PWM input and motor speed. The motor achieved a maximum measured speed of 147.44 RPM at PWM 255.

The resulting calibration data will be used to implement feedforward compensation alongside PI feedback control. This approach is intended to improve setpoint tracking and reduce steady-state error.

## 7. Next Steps

- [x] Establish PWM-to-RPM relationship
- [x] Determine maximum measured motor speed
- [ ] Implement feedforward compensation
- [ ] Combine feedforward with PI feedback
- [ ] Tune proportional and integral gains
- [ ] Compare P, PI, and PID performance
- [ ] Measure rise time, settling time, and overshoot
- [ ] Evaluate disturbance rejection

---
