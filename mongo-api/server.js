require("dotenv").config();
const express = require("express");
const mongoose = require("mongoose");
const cors = require("cors");

const app = express();
const PORT = process.env.PORT || 5000;

// Middleware
app.use(express.json());
app.use(cors());

// Conexión a MongoDB
mongoose.connect(process.env.MONGO_URI).then(() => console.log("MongoDB conectado"))
  .catch(err => console.error("Error en la conexión:", err));

// Definir el esquema de la base de datoscode.c
const ItemSchema = new mongoose.Schema({
    name: String,
    value: Number
});
const Item = mongoose.model("Item", ItemSchema);

// Rutas de la API
app.get("/", (req, res) => {
    res.send("API funcionando 🚀");
});

// Obtener todos los ítems
app.get("/items", async (req, res) => {
    const items = await Item.find();
    res.json(items);
});

// Agregar un nuevo ítem
app.post("/items", async (req, res) => {
    const newItem = new Item(req.body);
    await newItem.save();
    res.json(newItem);
});

// Actualizar un ítem por ID
app.put("/items/:id", async (req, res) => {
    const updatedItem = await Item.findByIdAndUpdate(req.params.id, req.body, { new: true });
    res.json(updatedItem);
});

// Eliminar un ítem por ID
app.delete("/items/:id", async (req, res) => {
    await Item.findByIdAndDelete(req.params.id);
    res.json({ message: "Item eliminado" });
});

// Iniciar el servidor
app.listen(PORT, () => {
    console.log(`Servidor corriendo en http://localhost:${PORT}`);
});
