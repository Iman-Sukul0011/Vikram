import pandas as pd
import matplotlib.pyplot as plt

# Load the telemetry data
try:
    data = pd.read_csv('../Data/telemetry.csv') # Path to your logged data
    
    # Plotting Altitude vs. Pressure
    plt.figure(figsize=(10, 6))
    plt.plot(data['Alt'], data['Pres'], label='Pressure Gradient', color='b')
    plt.xlabel('Altitude (m)')
    plt.ylabel('Pressure (Pa)')
    plt.title('Vikram 1.0: Pressure vs. Altitude (Hydrostatic Validation)')
    plt.grid(True)
    plt.gca().invert_xaxis() # Descent usually goes from high to low alt
    
    plt.savefig('../Assets/flight_analysis.png')
    print("Graph saved to Assets folder!")
    plt.show()
except Exception as e:
    print(f"Error: {e}. Make sure telemetry.csv exists in the Data folder.")