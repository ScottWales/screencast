#!/usr/bin/env python
"""
file:   timer.py
author: Scott Wales (scott.wales@unimelb.edu.au)

Copyright 2013 ARC Centre of Excellence for Climate System Science

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""

import Tkinter as tk
from datetime import datetime
from time import sleep

class TimerWindow:
    def __init__(self, master):
        self.start = datetime.now()
        self.runtime = tk.StringVar()
        label = tk.Label(master, font=("Helvetica",30), textvariable = self.runtime)
        label.pack()
        root.after(1000,lambda: self.update())
    def update(self):
        self.runtime.set(str(datetime.now() - self.start))
        root.after(1000,lambda: self.update())

root = tk.Tk()

timer = TimerWindow(root)

root.mainloop()
