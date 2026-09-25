function AdminDashboard() {
  const users = [
    {
      id: 1,
      name: 'Geetha',
      email: 'geetha@example.com',
      role: 'BUYER',
    },
    {
      id: 2,
      name: 'Test Seller',
      email: 'seller@test.com',
      role: 'SELLER',
    },
    {
      id: 3,
      name: 'Admin',
      email: 'admin@geethamart.com',
      role: 'ADMIN',
    },
  ];

  const orders = [
    {
      id: 101,
      buyer: 'Geetha',
      total: 325,
      status: 'CONFIRMED',
    },
    {
      id: 102,
      buyer: 'Priya',
      total: 450,
      status: 'SHIPPED',
    },
    {
      id: 103,
      buyer: 'Arun',
      total: 180,
      status: 'PENDING',
    },
  ];

  const products = [
    {
      id: 1,
      name: 'Fresh Apples',
      seller: 'Test Seller',
      price: 120,
      stock: 25,
    },
    {
      id: 2,
      name: 'Organic Rice',
      seller: 'Test Seller',
      price: 85,
      stock: 40,
    },
    {
      id: 3,
      name: 'Fresh Milk',
      seller: 'Test Seller',
      price: 60,
      stock: 30,
    },
  ];

  return (
    <div className="admin-dashboard">
      <div className="admin-dashboard-header">
        <div>
          <p>GEETHAMART ADMIN</p>

          <h1>Admin Dashboard</h1>

          <span>
            Manage users, orders and products
          </span>
        </div>
      </div>

      <div className="admin-stats">
        <div className="admin-stat-card">
          <p>Total Users</p>
          <h2>{users.length}</h2>
        </div>

        <div className="admin-stat-card">
          <p>Total Orders</p>
          <h2>{orders.length}</h2>
        </div>

        <div className="admin-stat-card">
          <p>Total Products</p>
          <h2>{products.length}</h2>
        </div>

        <div className="admin-stat-card">
          <p>Pending Orders</p>
          <h2>
            {
              orders.filter(
                (order) =>
                  order.status === 'PENDING'
              ).length
            }
          </h2>
        </div>
      </div>

      {/* USERS */}

      <div className="admin-section-card">
        <div className="admin-section-header">
          <div>
            <h2>Users</h2>

            <p>
              View registered GeethaMart users
            </p>
          </div>
        </div>

        <div className="admin-table-wrapper">
          <table className="admin-table">
            <thead>
              <tr>
                <th>ID</th>
                <th>Name</th>
                <th>Email</th>
                <th>Role</th>
              </tr>
            </thead>

            <tbody>
              {users.map((user) => (
                <tr key={user.id}>
                  <td>{user.id}</td>

                  <td>
                    <strong>{user.name}</strong>
                  </td>

                  <td>{user.email}</td>

                  <td>
                    <span className="admin-role">
                      {user.role}
                    </span>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      </div>

      {/* ORDERS */}

      <div className="admin-section-card">
        <div className="admin-section-header">
          <div>
            <h2>Orders</h2>

            <p>
              View and monitor customer orders
            </p>
          </div>
        </div>

        <div className="admin-table-wrapper">
          <table className="admin-table">
            <thead>
              <tr>
                <th>Order ID</th>
                <th>Buyer</th>
                <th>Total</th>
                <th>Status</th>
              </tr>
            </thead>

            <tbody>
              {orders.map((order) => (
                <tr key={order.id}>
                  <td>
                    #{order.id}
                  </td>

                  <td>
                    <strong>
                      {order.buyer}
                    </strong>
                  </td>

                  <td>
                    ₹{order.total}
                  </td>

                  <td>
                    <span
                      className={`admin-order-status ${order.status.toLowerCase()}`}
                    >
                      {order.status}
                    </span>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      </div>

      {/* PRODUCTS */}

      <div className="admin-section-card">
        <div className="admin-section-header">
          <div>
            <h2>Products</h2>

            <p>
              Manage products listed by sellers
            </p>
          </div>
        </div>

        <div className="admin-table-wrapper">
          <table className="admin-table">
            <thead>
              <tr>
                <th>Product</th>
                <th>Seller</th>
                <th>Price</th>
                <th>Stock</th>
                <th>Action</th>
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
                    {product.seller}
                  </td>

                  <td>
                    ₹{product.price}
                  </td>

                  <td>
                    {product.stock}
                  </td>

                  <td>
                    <button className="admin-delete-button">
                      Remove
                    </button>
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

export default AdminDashboard;