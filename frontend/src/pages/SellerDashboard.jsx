function SellerDashboard() {
  const products = [
    {
      id: 1,
      name: 'Fresh Apples',
      category: 'Fruits',
      price: 120,
      stock: 25,
      status: 'Available',
    },
    {
      id: 2,
      name: 'Organic Rice',
      category: 'Groceries',
      price: 85,
      stock: 40,
      status: 'Available',
    },
    {
      id: 3,
      name: 'Fresh Milk',
      category: 'Dairy',
      price: 60,
      stock: 5,
      status: 'Low Stock',
    },
  ];

  return (
    <div className="seller-dashboard">
      <div className="seller-dashboard-header">
        <div>
          <p>GEETHAMART SELLER</p>

          <h1>Seller Dashboard</h1>

          <span>
            Manage your products and inventory
          </span>
        </div>

        <button className="add-product-button">
          + Add Product
        </button>
      </div>

      <div className="seller-stats">
        <div className="seller-stat-card">
          <p>Total Products</p>
          <h2>3</h2>
        </div>

        <div className="seller-stat-card">
          <p>Available Stock</p>
          <h2>70</h2>
        </div>

        <div className="seller-stat-card">
          <p>Low Stock</p>
          <h2>1</h2>
        </div>

        <div className="seller-stat-card">
          <p>Total Sales</p>
          <h2>₹12,450</h2>
        </div>
      </div>

      <div className="seller-products-card">
        <div className="seller-products-header">
          <div>
            <h2>My Products</h2>

            <p>
              Manage products listed in your store
            </p>
          </div>

          <input
            type="text"
            placeholder="Search products..."
          />
        </div>

        <div className="seller-table-wrapper">
          <table className="seller-products-table">
            <thead>
              <tr>
                <th>Product</th>
                <th>Category</th>
                <th>Price</th>
                <th>Stock</th>
                <th>Status</th>
                <th>Actions</th>
              </tr>
            </thead>

            <tbody>
              {products.map((product) => (
                <tr key={product.id}>
                  <td>
                    <strong>
                      {product.name}
                    </strong>
                  </td>

                  <td>
                    {product.category}
                  </td>

                  <td>
                    ₹{product.price}
                  </td>

                  <td>
                    {product.stock}
                  </td>

                  <td>
                    <span
                      className={
                        product.status === 'Low Stock'
                          ? 'seller-status low-stock'
                          : 'seller-status available'
                      }
                    >
                      {product.status}
                    </span>
                  </td>

                  <td>
                    <div className="seller-actions">
                      <button>
                        Edit
                      </button>

                      <button>
                        Delete
                      </button>
                    </div>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
}

export default SellerDashboard;