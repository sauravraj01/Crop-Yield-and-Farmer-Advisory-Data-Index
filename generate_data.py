
import random

random.seed(42)

# Western UP demonstration coordinate bounds
LAT_MIN, LAT_MAX = 28.0, 29.5
LON_MIN, LON_MAX = 77.0, 78.5

# Generate weather observations
with open("data/weather.txt", "w") as file:
    for i in range(1, 501):
        lat = random.uniform(LAT_MIN, LAT_MAX)
        lon = random.uniform(LON_MIN, LON_MAX)

        temperature = random.uniform(12, 42)
        humidity = random.uniform(25, 95)
        rainfall = random.uniform(0, 30)

        file.write(
            f"W{i},{lat:.4f},{lon:.4f},"
            f"{temperature:.2f},{humidity:.2f},{rainfall:.2f}\n"
        )

# Generate soil observations
with open("data/soil.txt", "w") as file:
    for i in range(1, 501):
        lat = random.uniform(LAT_MIN, LAT_MAX)
        lon = random.uniform(LON_MIN, LON_MAX)

        ph = random.uniform(5.0, 8.5)
        moisture = random.uniform(10, 65)
        nitrogen = random.uniform(100, 400)
        phosphorus = random.uniform(10, 80)
        potassium = random.uniform(50, 400)

        file.write(
            f"S{i},{lat:.4f},{lon:.4f},{ph:.2f},"
            f"{moisture:.2f},{nitrogen:.2f},"
            f"{phosphorus:.2f},{potassium:.2f}\n"
        )

# Generate disease records

crops = {
    "Wheat": [
        ("Rust", "Orange brown pustules on leaves", "Monitor disease spread and seek expert guidance"),
        ("Smut", "Dark fungal growth on grains", "Use certified disease free seeds"),
        ("Powdery Mildew", "White powdery growth on leaves", "Monitor crop health and seek expert guidance"),
        ("Loose Smut", "Black powdery spores replacing grains", "Use healthy certified seeds"),
        ("Fusarium Head Blight", "Discolored spikelets and shrivelled grains", "Monitor crop and consult an agricultural expert")
    ],

    "Rice": [
        ("Blast", "Spindle shaped lesions on leaves", "Monitor disease spread and seek expert guidance"),
        ("Sheath Blight", "Lesions on leaf sheaths", "Follow recommended crop management practices"),
        ("Brown Spot", "Brown spots on leaves", "Monitor crop health and soil nutrient conditions"),
        ("Bacterial Leaf Blight", "Yellowing and drying of leaf edges", "Use recommended disease management practices"),
        ("False Smut", "Yellowish green fungal balls on grains", "Use healthy seeds and monitor crop health")
    ],

    "Maize": [
        ("Leaf Blight", "Long greyish lesions on leaves", "Monitor crop and seek expert guidance"),
        ("Common Rust", "Reddish brown pustules on leaves", "Monitor disease spread"),
        ("Downy Mildew", "Pale stripes on leaves", "Use healthy seeds and monitor crop health"),
        ("Stalk Rot", "Weak and discolored stalks", "Monitor crop condition and seek expert advice"),
        ("Leaf Spot", "Small brown spots on leaves", "Follow recommended crop management practices")
    ],

    "Sugarcane": [
        ("Red Rot", "Red discoloration inside the stalk", "Use healthy planting material"),
        ("Smut", "Black whip like fungal growth", "Use disease free planting material"),
        ("Smut Whip", "Dark whip shaped growth from shoots", "Monitor crop and seek expert guidance"),
        ("Wilt", "Yellowing and drying of leaves", "Check crop health and consult an expert"),
        ("Rust", "Reddish brown pustules on leaves", "Monitor disease spread")
    ],

    "Potato": [
        ("Early Blight", "Dark concentric spots on leaves", "Monitor crop and seek expert guidance"),
        ("Late Blight", "Dark lesions on leaves", "Seek timely agricultural expert guidance"),
        ("Black Scurf", "Dark patches on tuber surface", "Use healthy planting material"),
        ("Common Scab", "Rough corky patches on tubers", "Monitor soil and crop conditions"),
        ("Bacterial Wilt", "Sudden wilting of plants", "Use certified disease free planting material")
    ],

    "Tomato": [
        ("Early Blight", "Dark circular spots on leaves", "Monitor disease spread"),
        ("Late Blight", "Water soaked lesions on leaves", "Seek expert guidance promptly"),
        ("Bacterial Wilt", "Sudden wilting of plants", "Use healthy planting material"),
        ("Leaf Curl", "Curling and yellowing of leaves", "Monitor pest activity and seek expert guidance"),
        ("Septoria Leaf Spot", "Small circular spots on leaves", "Follow recommended crop management practices")
    ],

    "Cotton": [
        ("Bacterial Blight", "Angular water soaked leaf spots", "Use healthy seeds and monitor crop health"),
        ("Fusarium Wilt", "Yellowing and wilting of plants", "Monitor affected plants and seek expert advice"),
        ("Grey Mildew", "Greyish growth on leaf surfaces", "Monitor crop and consult an expert"),
        ("Root Rot", "Root discoloration and plant wilting", "Check soil and crop conditions"),
        ("Cotton Leaf Curl", "Upward curling and thickened leaves", "Monitor whitefly activity and seek expert advice")
    ],

    "Chickpea": [
        ("Fusarium Wilt", "Yellowing and wilting of plants", "Use healthy seeds and monitor crop health"),
        ("Ascochyta Blight", "Brown lesions on leaves and stems", "Monitor disease spread"),
        ("Dry Root Rot", "Dry and discolored roots", "Check soil and crop conditions"),
        ("Collar Rot", "Rotting near the plant base", "Use healthy seeds"),
        ("Rust", "Small reddish brown pustules on leaves", "Monitor crop health")
    ],

    "Mustard": [
        ("Alternaria Blight", "Dark concentric spots on leaves", "Monitor disease spread"),
        ("White Rust", "White raised pustules on leaves", "Consult an agricultural expert"),
        ("Downy Mildew", "Yellow patches on upper leaf surfaces", "Monitor crop condition"),
        ("Powdery Mildew", "White powdery growth on leaves", "Follow recommended crop management practices"),
        ("Sclerotinia Stem Rot", "Water soaked lesions on stems", "Monitor affected plants")
    ],

    "Groundnut": [
        ("Tikka Disease", "Dark spots on groundnut leaves", "Monitor crop health"),
        ("Rust", "Reddish brown pustules on leaves", "Monitor disease spread"),
        ("Collar Rot", "Rotting near the stem base", "Use healthy planting material"),
        ("Stem Rot", "White fungal growth near plant base", "Monitor soil and crop conditions"),
        ("Bud Necrosis", "Necrosis and distortion of young leaves", "Monitor pest activity and seek expert advice")
    ]
}


disease_count = 0

with open("data/diseases.txt", "w") as file:
    for crop, disease_list in crops.items():
        for disease, symptoms, advisory in disease_list:
            file.write(
                f"{crop},{disease},{symptoms},{advisory}\n"
            )
            disease_count += 1

print("Synthetic dataset generated successfully!")
print("Weather records: 500")
print("Soil records: 500")
print("Disease records:", disease_count)



# Historical crop yield dataset

crop_yields = {
    "Wheat": (3.0, 5.5, "Rabi"),
    "Rice": (2.5, 6.0, "Kharif"),
    "Maize": (2.0, 5.0, "Kharif"),
    "Sugarcane": (55.0, 85.0, "Annual"),
    "Potato": (20.0, 35.0, "Rabi"),
    "Tomato": (25.0, 50.0, "Rabi"),
    "Cotton": (1.5, 3.0, "Kharif"),
    "Chickpea": (0.8, 2.0, "Rabi"),
    "Mustard": (1.0, 2.2, "Rabi"),
    "Groundnut": (1.0, 2.5, "Kharif")
}

yield_count = 0

with open("data/yield.txt", "w") as file:

    for crop, values in crop_yields.items():

        min_yield, max_yield, season = values

        for year in range(2021, 2026):

            for j in range(10):

                lat = random.uniform(28.0, 29.5)
                lon = random.uniform(77.0, 78.5)

                area = random.uniform(0.5, 5.0)

                yield_value = random.uniform(
                    min_yield, max_yield
                )

                production = area * yield_value

                yield_count += 1

                file.write(
                    f"Y{yield_count},{crop},{year},{season},"
                    f"{lat:.4f},{lon:.4f},{area:.2f},"
                    f"{production:.2f},{yield_value:.2f}\n"
                )

print("Historical yield records:", yield_count)
