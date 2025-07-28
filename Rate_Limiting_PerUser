const express = require('express');
const app = express();

// Simulated Authentication Middleware
app.use((req, res, next) => {
  req.user = { id: 'user123' };
  next();
});

const WINDOW_MS = 60 * 1000;
const MAX_REQUESTS = 5;

// New structure: Map<userId, Map<route, Array<timestamps>>>
const userRouteMap = new Map();

function userRouteRateLimiter(req, res, next) {
  const userId = req.user?.id;
  const route = req.path; // This is the route path like "/profile", "/settings"

  if (!userId) {
    return res.status(401).json({ error: 'Authentication required' });
  }

  const currentTime = Date.now();

  // Initialize map for user if doesn't exist
  if (!userRouteMap.has(userId)) {
    userRouteMap.set(userId, new Map());
  }

  const routeMap = userRouteMap.get(userId);
  const requestTimestamps = routeMap.get(route) || [];

  // Filter timestamps within the window
  const validTimestamps = requestTimestamps.filter(ts => currentTime - ts < WINDOW_MS);

  if (validTimestamps.length >= MAX_REQUESTS) {
    return res.status(429).json({
      error: `Too many requests to ${route}. Try again later.`,
    });
  }

  // Push current timestamp and update map
  validTimestamps.push(currentTime);
  routeMap.set(route, validTimestamps);
  userRouteMap.set(userId, routeMap);

  next();
}

// Apply rate limiter to all or specific routes
app.use(userRouteRateLimiter);

app.get('/profile', (req, res) => {
  res.send(`Welcome to your profile, ${req.user.id}`);
});

app.get('/settings', (req, res) => {
  res.send(`Welcome to your settings, ${req.user.id}`);
});

app.get('/dashboard', (req, res) => {
  res.send(`Welcome to dashboard, ${req.user.id}`);
});

app.listen(3000, () => {
  console.log('Server running at http://localhost:3000');
});
