import { useState } from 'react';
import './App.css';

import Login from './pages/Login';
import Register from './pages/Register';
import Products from './pages/Products';
import Cart from './pages/Cart';
import Checkout from './pages/Checkout';
import SellerDashboard from './pages/SellerDashboard';
import AdminDashboard from './pages/AdminDashboard';

function App() {
  const [page, setPage] = useState('home');

  const [cartItems, setCartItems] = useState([]);

  const products = [
    {
      id: 1,
      name: 'Fresh Apples',
      category: 'Fruits',
      price: 120,
      image: '🍎',
    },
    {
      id: 2,
      name: 'Organic Rice',
      category: 'Groceries',
      price: 85,
      image: '🍚',
    },
    {
      id: 3,
      name: 'Fresh Milk',
      category: 'Dairy',
      price: 60,
      image: '🥛',
    },
    {
      id: 4,
      name: 'Potato Chips',
      category: 'Snacks',
      price: 40,
      image: '🥔',
    },
  ];

  const addToCart = (product) => {
    setCartItems((currentItems) => {
      const existingItem = currentItems.find(
        (item) => item.id === product.id
      );

      if (existingItem) {
        return currentItems.map((item) =>
          item.id === product.id
            ? {
                ...item,
                quantity: item.quantity + 1,
              }
            : item
        );
      }

      return [
        ...currentItems,
        {
          ...product,
          quantity: 1,
        },
      ];
    });
  };

  const increaseQuantity = (id) => {
    setCartItems((currentItems) =>
      currentItems.map((item) =>
        item.id === id
          ? {
              ...item,
              quantity: item.quantity + 1,
            }
          : item
      )
    );
  };

  const decreaseQuantity = (id) => {
    setCartItems((currentItems) =>
      currentItems
        .map((item) =>
          item.id === id
            ? {
                ...item,
                quantity: item.quantity - 1,
              }
            : item
        )
        .filter((item) => item.quantity > 0)
    );
  };

  const removeFromCart = (id) => {
    setCartItems((currentItems) =>
      currentItems.filter(
        (item) => item.id !== id
      )
    );
  };

  const clearCart = () => {
    setCartItems([]);
  };

  if (page === 'login') {
    return (
      <div>
        <Login
          onRegister={() => setPage('register')}
        />

        <button
          className="back-home-button"
          onClick={() => setPage('home')}
        >
          ← Back to Home
        </button>
      </div>
    );
  }

  if (page === 'register') {
    return (
      <div>
        <Register
          onLogin={() => setPage('login')}
        />

        <button
          className="back-home-button"
          onClick={() => setPage('home')}
        >
          ← Back to Home
        </button>
      </div>
    );
  }

  if (page === 'products') {
    return (
      <div>
        <Products
          onAddToCart={addToCart}
        />

        <button
          className="back-home-button"
          onClick={() => setPage('home')}
        >
          ← Back to Home
        </button>
      </div>
    );
  }

  if (page === 'cart') {
    return (
      <div>
        <Cart
          cartItems={cartItems}
          onIncrease={increaseQuantity}
          onDecrease={decreaseQuantity}
          onRemove={removeFromCart}
          onCheckout={() => setPage('checkout')}
        />

        <button
          className="back-home-button"
          onClick={() => setPage('home')}
        >
          ← Back to Home
        </button>
      </div>
    );
  }

  if (page === 'checkout') {
    return (
      <div>
        <Checkout
          cartItems={cartItems}
          onClearCart={clearCart}
        />

        <button
          className="back-home-button"
          onClick={() => setPage('home')}
        >
          ← Back to Home
        </button>
      </div>
    );
  }

  if (page === 'seller') {
    return (
      <div>
        <SellerDashboard />

        <button
          className="back-home-button"
          onClick={() => setPage('home')}
        >
          ← Back to Home
        </button>
      </div>
    );
  }

  if (page === 'admin') {
    return (
      <div>
        <AdminDashboard />

        <button
          className="back-home-button"
          onClick={() => setPage('home')}
        >
          ← Back to Home
        </button>
      </div>
    );
  }

  return (
    <div className="app">
      <nav className="navbar">
        <div className="logo">
          <span className="logo-icon">🛒</span>
          <span>GeethaMart</span>
        </div>

        <div className="nav-links">
          <button
            className="nav-home-button"
            onClick={() => setPage('home')}
          >
            Home
          </button>

          <button
            className="nav-text-button"
            onClick={() => setPage('products')}
          >
            Products
          </button>

          <a href="#categories">
            Categories
          </a>

          <button
            className="nav-text-button cart-link"
            onClick={() => setPage('cart')}
          >
            🛒 Cart
            {cartItems.length > 0 &&
              ` (${cartItems.reduce(
                (sum, item) =>
                  sum + item.quantity,
                0
              )})`}
          </button>

          <button
            className="nav-text-button"
            onClick={() => setPage('seller')}
          >
            Seller
          </button>

          <button
            className="nav-text-button"
            onClick={() => setPage('admin')}
          >
            Admin
          </button>

          <button
            className="login-nav-button"
            onClick={() => setPage('login')}
          >
            Login
          </button>
        </div>
      </nav>

      <main>
        <section className="hero" id="home">
          <div className="hero-content">
            <p className="hero-label">
              WELCOME TO GEETHAMART
            </p>

            <h1>
              Everything you need,
              <span> all in one place.</span>
            </h1>

            <p className="hero-text">
              Shop quality products at great prices with
              GeethaMart.
            </p>

            <button
              className="shop-button"
              onClick={() => setPage('products')}
            >
              Shop Now
            </button>
          </div>
        </section>

        <section
          className="categories"
          id="categories"
        >
          <div className="section-heading">
            <p>EXPLORE</p>
            <h2>Shop by Category</h2>
          </div>

          <div className="category-grid">
            <div className="category-card">
              <span>🍎</span>
              <h3>Fruits</h3>
            </div>

            <div className="category-card">
              <span>🛒</span>
              <h3>Groceries</h3>
            </div>

            <div className="category-card">
              <span>🥛</span>
              <h3>Dairy</h3>
            </div>

            <div className="category-card">
              <span>🍪</span>
              <h3>Snacks</h3>
            </div>
          </div>
        </section>

        <section
          className="products"
          id="products"
        >
          <div className="section-heading">
            <p>OUR STORE</p>
            <h2>Popular Products</h2>
          </div>

          <div className="product-grid">
            {products.map((product) => (
              <div
                className="product-card"
                key={product.id}
              >
                <div className="product-image">
                  <span>{product.image}</span>
                </div>

                <div className="product-info">
                  <p className="product-category">
                    {product.category}
                  </p>

                  <h3>{product.name}</h3>

                  <div className="product-bottom">
                    <strong>
                      ₹{product.price}
                    </strong>

                    <button
                      onClick={() =>
                        addToCart(product)
                      }
                    >
                      Add to Cart
                    </button>
                  </div>
                </div>
              </div>
            ))}
          </div>
        </section>
      </main>

      <footer>
        <p>
          © 2026 GeethaMart. All rights reserved.
        </p>
      </footer>
    </div>
  );
}

export default App;