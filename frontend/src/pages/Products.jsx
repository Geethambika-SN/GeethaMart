import { useState } from 'react';

function Products({ onAddToCart }) {
  const [searchTerm, setSearchTerm] = useState('');
  const [selectedCategory, setSelectedCategory] =
    useState('ALL');

  const products = [
    {
      id: 1,
      name: 'Fresh Apples',
      category: 'Fruits',
      price: 120,
      image: '🍎',
      stock: 25,
    },
    {
      id: 2,
      name: 'Organic Rice',
      category: 'Groceries',
      price: 85,
      image: '🍚',
      stock: 40,
    },
    {
      id: 3,
      name: 'Fresh Milk',
      category: 'Dairy',
      price: 60,
      image: '🥛',
      stock: 30,
    },
    {
      id: 4,
      name: 'Potato Chips',
      category: 'Snacks',
      price: 40,
      image: '🥔',
      stock: 50,
    },
    {
      id: 5,
      name: 'Fresh Bananas',
      category: 'Fruits',
      price: 50,
      image: '🍌',
      stock: 35,
    },
    {
      id: 6,
      name: 'Wheat Flour',
      category: 'Groceries',
      price: 70,
      image: '🌾',
      stock: 20,
    },
    {
      id: 7,
      name: 'Curd',
      category: 'Dairy',
      price: 45,
      image: '🥣',
      stock: 18,
    },
    {
      id: 8,
      name: 'Biscuits',
      category: 'Snacks',
      price: 30,
      image: '🍪',
      stock: 45,
    },
  ];

  const handleAddToCart = (product) => {
    onAddToCart(product);

    alert(`${product.name} added to cart!`);
  };

  const filteredProducts = products.filter(
    (product) => {
      const search =
        searchTerm.toLowerCase().trim();

      const matchesSearch =
        product.name
          .toLowerCase()
          .includes(search) ||
        product.category
          .toLowerCase()
          .includes(search);

      const matchesCategory =
        selectedCategory === 'ALL' ||
        product.category === selectedCategory;

      return (
        matchesSearch &&
        matchesCategory
      );
    }
  );

  return (
    <div className="products-page">
      <div className="products-page-header">
        <p>GEETHAMART STORE</p>

        <h1>All Products</h1>

        <span>
          Browse our available products
        </span>
      </div>

      <div className="product-filters">
        <input
          type="text"
          placeholder="Search products or categories..."
          value={searchTerm}
          onChange={(event) =>
            setSearchTerm(event.target.value)
          }
        />

        <select
          value={selectedCategory}
          onChange={(event) =>
            setSelectedCategory(
              event.target.value
            )
          }
        >
          <option value="ALL">
            All Categories
          </option>

          <option value="Fruits">
            Fruits
          </option>

          <option value="Groceries">
            Groceries
          </option>

          <option value="Dairy">
            Dairy
          </option>

          <option value="Snacks">
            Snacks
          </option>
        </select>
      </div>

      <div className="products-page-grid">
        {filteredProducts.map((product) => (
          <div
            className="products-page-card"
            key={product.id}
          >
            <div className="products-page-image">
              <span>{product.image}</span>
            </div>

            <div className="products-page-info">
              <p className="products-page-category">
                {product.category}
              </p>

              <h2>{product.name}</h2>

              <p className="products-page-stock">
                {product.stock} items available
              </p>

              <div className="products-page-bottom">
                <strong>
                  ₹{product.price}
                </strong>

                <button
                  onClick={() =>
                    handleAddToCart(product)
                  }
                >
                  Add to Cart
                </button>
              </div>
            </div>
          </div>
        ))}
      </div>

      {filteredProducts.length === 0 && (
        <p
          style={{
            textAlign: 'center',
            marginTop: '40px',
            color: '#6b7280',
          }}
        >
          No products found.
        </p>
      )}
    </div>
  );
}

export default Products;