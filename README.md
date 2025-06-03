# 🚄 Maglev Superconductor Simulator

A C++ console simulation where you manage a futuristic maglev train powered by superconductors—because why let your old superconductors rot in the garage? 🧊⚡

## Features

- **Interactive dashboard:** Watch the train's position, speed, superconductor temperature, coolant level, maglev lift, and system status update live.
- **Levitation physics:** Only achieve lift when the superconductor is cooled below its critical temperature (Tc). Otherwise… enjoy a “quench” warning!
- **Resource management:** Control the train's speed, superconductor current, coolant use, and temperature.
- **Manual controls:** Adjust all the key variables, refill coolant, toggle cooling, and try to reach the end of the track.

## How to Play

1. **Compile the program:**
    ```bash
    g++ maglev.cpp -o maglev
    ```

2. **Run the simulation:**
    ```bash
    ./maglev
    ```

3. **Use the controls:**
    - `[1]` Set the superconductor current (Amps). Higher current = more maglev lift!
    - `[2]` Set train speed (m/s). The train only moves if it's levitating.
    - `[3]` Toggle cooling on/off. Cooling uses up coolant and drops the superconductor temperature.
    - `[4]` Refill coolant to 100%.
    - `[5]` Quit the simulation.

4. **Goal:**  
   Get your maglev train to the end of the 100-meter track **without quenching or running out of coolant**!

---

## How It Works

- The superconductor must be cooled below Tc (critical temp, 90 K) to levitate the train.
- You can only move the train when maglev lift is enough to support at least 90% of the train’s weight.
- Coolant gets used up while cooling is on. If coolant runs out or you turn off cooling, the temperature rises!
- If you set a high current with the superconductor too warm, you’ll get a **QUENCH! (No Levitation)** warning.

---

## Tips & Tricks

- **Start cooling immediately!** It takes a while to drop from room temperature (300 K) to below 90 K.
- **Set current high** (close to 500 A) for maximum lift.
- **Keep an eye on coolant!** Refill before you run out, or you’ll lose levitation.
- **Try different speeds** and see how fast you can reach the finish line.

---

## Possible Expansions

- Add random events (coolant leaks, power surges, etc.)
- Make acceleration realistic (force = mass × acceleration)
- Add ASCII train art for extra flavor
- Implement achievements (“100m in under 10 ticks!”)

---

## Requirements

- C++ compiler (e.g. g++, clang++)
- Runs in any terminal (tested on macOS, Linux, Windows)

---

## License

MIT (Do whatever you want, but send memes if you enjoy it.)

---

Made with ❤️, superconductors, and way too much coolant.
