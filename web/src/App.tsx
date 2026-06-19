import { useEffect } from 'react';
import Home from './view/Home';

export default function App() {
  useEffect(()=>{

  });
  return (
    <div className="min-h-svh">
      <Home />
      {/* <div className="font-mono text-xs text-muted-foreground">
        (Press <kbd>d</kbd> to toggle dark mode)
      </div> */}
    </div>
  )
}
