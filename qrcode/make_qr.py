import tkinter as tk
from tkinter import filedialog, messagebox
import qrcode
# from PIL import Image  <-- This import is not actually needed here
                       # The 'qrcode' library uses it internally.

def generate_qr():
    url = entry_url.get()
    
    if not url:
        messagebox.showwarning("Warning", "Please enter a URL or text first!")
        return

    try:
        file_path = filedialog.asksaveasfilename(
            defaultextension=".png",
            filetypes=[("PNG files", "*.png"), ("All files", "*.*")],
            title="Save QR Code As..."
        )
        
        if not file_path:
            return

        img = qrcode.make(url)
        img.save(file_path)
        
        messagebox.showinfo("Success", f"QR Code saved successfully to:\n{file_path}")

    except Exception as e:
        messagebox.showerror("Error", f"An error occurred: {e}")

# --- New function to center the window ---
def center_window(win):
    # First, update the window to get its 'natural' size
    win.update_idletasks()
    
    # Get the window's calculated size
    width = win.winfo_width()
    height = win.winfo_height()
    
    # Get the screen's size
    screen_width = win.winfo_screenwidth()
    screen_height = win.winfo_screenheight()
    
    # Calculate the x and y coordinates to center the window
    x = (screen_width // 2) - (width // 2)
    y = (screen_height // 2) - (height // 2)
    
    # Set the window's position
    win.geometry(f'{width}x{height}+{x}+{y}')

# --- Set up the App Window ---
root = tk.Tk()
root.title("Free QR Code Generator")
# root.geometry("400x150")  <-- REMOVED THIS LINE

# --- Create a main frame to hold all widgets ---
# This lets us add padding around the *entire* app
main_frame = tk.Frame(root)
# 'fill' and 'expand' make the frame grow if the user resizes the window
main_frame.pack(padx=10, pady=10, fill='x', expand=True)

# Create a label
label_url = tk.Label(main_frame, text="Enter URL or Text:")
label_url.pack(pady=5)

# Create a text entry box
entry_url = tk.Entry(main_frame)
# 'fill' and 'expand' make the entry box stretch horizontally
entry_url.pack(pady=5, padx=5, fill='x', expand=True)

# Create the "Generate" button
generate_button = tk.Button(main_frame, text="Generate QR Code", command=generate_qr)
generate_button.pack(pady=10)

# --- Call the centering function ---
center_window(root)

# Start the app
root.mainloop()
